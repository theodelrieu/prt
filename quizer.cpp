#include "quizer.hpp"
#include "range.hpp"

#include <iostream>
inline auto constexpr correctAnswerText = "<font color=\"green\"><b>Correct!</b></font>";
inline auto constexpr wrongAnswerText = "<font color=\"red\"><b>Wrong!</b></font>";

namespace
{
int indexOfHandInGrid(HandInfo const& hand)
{
    auto const& grid = emptyHandInfo();
    auto const it = std::find_if(grid.begin(), grid.end(), [&](auto const &h) {
        return h.name() == hand.name();
    });

    return std::distance(grid.begin(), it);
}
}

Quizer::Quizer(RangeDisplayer const* displayer, QObject *parent) : QObject(parent), _displayer(displayer), _rng(std::random_device{}())
{

}

void Quizer::start()
{
    auto const settings = _displayer->quizSettings();
    auto handInfo = _displayer->handInfo();

    _quizHands.insert(_quizHands.end(), handInfo.begin(), handInfo.end());

    auto const excludedSubranges = settings->excludedSubranges();
    for (auto const& excluded : qAsConst(excludedSubranges))
    {
        _quizHands.erase(
                    std::remove_if(_quizHands.begin(), _quizHands.end(), [&](auto const& hand) {
            if (hand.parentRange().weight() == 0)
                return true;
            auto const& subranges = hand.subranges();
            auto it = std::find_if(subranges.begin(), subranges.end(), [&](auto const& sub) {
                // TODO use == when weight is moved out of RangeInfo
                return sub.name() == excluded.name() && sub.color() == excluded.color();
            });
            if (it != subranges.end())
                return it->weight() == 100;
            return false;
        }),
                    _quizHands.end());
    }
    if (_quizHands.empty())
    {
        // TODO emit error
        return;
    }
    nextQuiz();
}

void Quizer::next()
{
    nextQuiz();
}

void Quizer::answer(int buttonIndex)
{
    _totalAttempts++;
    auto const isCorrect = buttonIndex == _correctAnswerButtonIndex;
    _succeededAttempts += isCorrect;
    QString result = (isCorrect ? correctAnswerText : wrongAnswerText);
    result += " %1 / %2";
    emit answered(result.arg(_succeededAttempts).arg(_totalAttempts));
}

void Quizer::stop()
{
    _totalAttempts = 0;
    _succeededAttempts = 0;
    _quizHands.clear();
}

auto Quizer::nextQuizParams() -> std::tuple<QuizType, HandInfo const*, int>
{
    std::uniform_int_distribution<int> distrib(0, _quizHands.size());
    auto const idx = distrib(_rng);
    auto const& hand = _quizHands[idx];
    auto const gridIdx = indexOfHandInGrid(hand);

    // no subranges, simply quiz about the parent range
    if (_displayer->currentRange()->subrangeInfo().empty())
        return {QuizType::InBaseRange, std::addressof(hand), gridIdx};
    std::uniform_int_distribution quizTypeDistrib(0, 1);
    return {static_cast<QuizType>(1 + quizTypeDistrib(_rng)), std::addressof(hand), gridIdx};
}

void Quizer::nextInSubrangeQuiz(HandInfo const* hand, int handIndex)
{
    auto const& subrangeInfo = _displayer->currentRange()->subrangeInfo();
    std::uniform_int_distribution<int> distrib(0, subrangeInfo.size() - 1);
    auto const subrangeIndex = distrib(_rng);
    auto const& subrange = subrangeInfo.at(subrangeIndex);
    auto const hasSubrange = std::any_of(hand->subranges().begin(), hand->subranges().end(),
                         [&](auto const& sub){ return sub.name() == subrange.name() && sub.color() == subrange.color(); });
    auto const question = QString("Is <b>%1</b> in the <font color=\"%2\"><b>%3</b></font> range?")
            .arg(hand->name(), subrange.color().name(), subrange.name());
    QList<QuizChoice> choices{QuizChoice{"Yes"}, QuizChoice{"No"}};
    _correctAnswerButtonIndex = !hasSubrange;
    emit newQuiz(handIndex, question, choices);
}

void Quizer::nextMostPlayedQuiz(HandInfo const *hand, int handIndex)
{
    auto const& subrangeInfo = _displayer->currentRange()->subrangeInfo();
    auto subrangeIt = std::max_element(hand->subranges().begin(), hand->subranges().end(),
                       [&](auto const& lhs, auto const& rhs){ return lhs.weight() < rhs.weight(); });
    // TODO throw?
    if (subrangeIt == hand->subranges().end())
        return;
    auto subrangeIndexIt = std::find_if(subrangeInfo.begin(), subrangeInfo.end(),
                        [&](auto const& elem) { return subrangeIt->name() == elem.name() && subrangeIt->color() == elem.color(); });
    if (subrangeIndexIt == subrangeInfo.end())
        return;
    _correctAnswerButtonIndex = std::distance(subrangeInfo.begin(), subrangeIndexIt);
    auto const question = QString("What is the most played for <b>%1</b>?").arg(hand->name());
    QList<QuizChoice> choices;
    for (auto const& sub : subrangeInfo)
        choices.append(QuizChoice{sub.name(), sub.color()});
    emit newQuiz(handIndex, question, choices);
}

void Quizer::nextQuiz()
{
    auto const [quizType, handInfo, gridIndex] = nextQuizParams();

    switch (quizType) {
        case QuizType::InBaseRange:
            return;
        case QuizType::InSubrange:
            nextInSubrangeQuiz(handInfo, gridIndex);
            break;
        case QuizType::MostPlayed:
            nextMostPlayedQuiz(handInfo, gridIndex);
            break;
    }
}
