#include "quizer.hpp"
#include "range.hpp"

#include <iostream>

Quizer::Quizer(RangeDisplayer* displayer, QObject *parent) : QObject(parent), _displayer(displayer), _rng(std::random_device{}())
{

}

void Quizer::start()
{
    std::cout << "start called" << std::endl;
  // FIXME construct handInfo once (with new)
    auto const& handInfo = _displayer->handInfo();
    auto const currentRange = _displayer->currentRange();
    auto const subrangeInfo = currentRange->subrangeInfo();
    // TODO handle parent range only
    if (subrangeInfo.empty())
        return;
    auto distrib = std::uniform_int_distribution<int>(0, 168);
    auto subrangeDistrib = std::uniform_int_distribution<int>(0, subrangeInfo.size() - 1);
    for (;;) {
        auto i = distrib(_rng);
        if (handInfo[i].parentRange().weight() == 0)
            continue;
        auto j = subrangeDistrib(_rng);
        emit newQuiz(i, subrangeInfo.at(j));
        break;
    }
}


void Quizer::stop()
{

}
