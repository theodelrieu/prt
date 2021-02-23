#include "rangeinfo.hpp"

RangeInfo::RangeInfo(QString const& name, QColor color, double weight):
    QStandardItem(), _name(name), _color(color), _weight(weight)
{
}

QString const& RangeInfo::name() const
{
    return _name;
}

QColor RangeInfo::color() const
{
    return _color;
}

double RangeInfo::weight() const
{
    return _weight;
}
