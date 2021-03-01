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

void Quizer::answer(bool b)
{
    _totalAttempts++;
    auto const isCorrect = b == _answer;
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

void Quizer::nextQuiz()
{
    // FIXME construct handInfo once (with new)
    auto const& handInfo = _displayer->handInfo();
    auto const currentRange = _displayer->currentRange();
    auto const subrangeInfo = currentRange->subrangeInfo();
    // TODO handle parent range only, and refactor this mess
    if (subrangeInfo.empty())
        return;
    auto distrib = std::uniform_int_distribution<int>(0, 168);
    auto subrangeDistrib = std::uniform_int_distribution<int>(0, subrangeInfo.size() - 1);
    for (;;) {
        auto i = distrib(_rng);
        if (handInfo[i].parentRange().weight() == 0)
            continue;
        auto j = subrangeDistrib(_rng);
        auto const& subrange = subrangeInfo.at(j);
        auto it = std::find_if(handInfo[i].subranges().begin(), handInfo[i].subranges().end(), [&](auto const& sub){ return sub.name() == subrange.name() && sub.color() == subrange.color();});
        _answer = it != handInfo[i].subranges().end();
        auto rgb = subrange.color().name();
        auto const question = QString("Is <b>%1</b> in the <font color=\"%2\"><b>%3</b></font> range?").arg(handInfo[i].name()).arg(rgb).arg(subrange.name());
        emit newQuiz(i, question);
        break;
    }
}
