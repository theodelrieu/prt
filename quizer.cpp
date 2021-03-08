#include "quizer.hpp"
#include "range.hpp"

#include <iostream>

Quizer::Quizer(RangeDisplayer* displayer, QObject *parent) : QObject(parent), _displayer(displayer), _rng(std::random_device{}())
{

}

void Quizer::start()
{
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
    QString result = (isCorrect ? "<font color=\"green\"><b>Correct!</b></font>" : "<font color=\"red\"><b>Wrong!</b></font>");
    result += " %1 / %2";
    emit answered(result.arg(_succeededAttempts).arg(_totalAttempts));
}

void Quizer::stop()
{
    _totalAttempts = 0;
    _succeededAttempts = 0;
}

auto Quizer::nextQuizParams() -> std::tuple<QuizType, HandInfo const*, int>
{
    // FIXME construct handInfo once (with new)
    auto const& handInfo = _displayer->handInfo();
    std::uniform_int_distribution distrib(0, 168);
    auto idx = distrib(_rng);
    // no subranges, simply quiz about the parent range
    if (_displayer->currentRange()->subrangeInfo().empty())
        return {QuizType::InBaseRange, std::addressof(handInfo[idx]), idx};
    while (handInfo[idx].parentRange().weight() == 0)
        idx = distrib(_rng);
    std::uniform_int_distribution quizTypeDistrib(0, 1);
    return {static_cast<QuizType>(quizTypeDistrib(_rng)), std::addressof(handInfo[idx]), idx};
}

void Quizer::nextInSubrangeQuiz(HandInfo const* hand, int handIndex)
{
    auto const& subrangeInfo = _displayer->currentRange()->subrangeInfo();
    std::uniform_int_distribution distrib(0, subrangeInfo.size() - 1);
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

void Quizer::nextQuiz()
{
    auto const [quizType, handInfo, handIndex] = nextQuizParams();
    nextInSubrangeQuiz(handInfo, handIndex);
            /*
    switch (quizType) {
    case QuizType::InBaseRange:
        nextInBaseRangeQuiz(handIndex);
    case QuizType::InSubrange:
        nextInSubrangeQuiz(handIndex);
    case QuizType::MostPlayed:
        nextMostPlayedQuiz(handIndex);
    }
            */
}
