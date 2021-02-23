#include "range.hpp"

#include <prc/combo.hpp>
#include <stdexcept>

Range::Range(prc::range const& range, QObject* parent) : QObject(parent), QStandardItem(), _range(range)
{
    setText(QString::fromStdString(range.name()));
}

int Range::type() const
{
    return QStandardItem::ItemType::UserType;
}

QVector<HandInfo> Range::toHandInfo() const
{
    // TODO find a way to show parent/subranges differently
    // TODO subranges
    auto ret = emptyHandInfo();
    for (auto const& [w, e] : _range.elems())
    {
        auto const hands = prc::expand_hands(e);
        for (auto const& h : hands)
        {
            auto const n = h.string();
            auto it = std::find_if(ret.begin(), ret.end(), [&n](auto& elem){ return elem.name().toStdString() == n; });
            if (it == ret.end())
                throw std::runtime_error("should not happen: invalid hand " + n);
            // TODO fix parent range color
            //it->ranges.append(RangeInfo{"Parent", QColor::fromRgb(0x949FE8), w});
        }
    }
    //auto hands = prc::expand_hands()
    return ret;
}
