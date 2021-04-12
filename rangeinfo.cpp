#include "rangeinfo.hpp"

RangeInfo::RangeInfo(QString const& name, QColor color, double weight):
    _name(name), _color(color), _weight(weight)
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

bool operator==(RangeInfo const& lhs, RangeInfo const& rhs)
{
   return lhs.name() == rhs.name() && lhs.color() == rhs.color() && lhs.weight() == rhs.weight();
}

bool operator!=(RangeInfo const& lhs, RangeInfo const& rhs)
{
    return !(lhs == rhs);
}
