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

QString Range::name() const
{
    return QString::fromStdString(_range.name());
}

QList<HandInfo> Range::toHandInfo() const
{
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
            it->setParentRange(RangeInfo{"Parent", QColor::fromRgb(0xa6a5a5), w});
        }
    }

    for (auto const& sub : _range.subranges())
    {
        for (auto const& [w, e]: sub.elems())
        {
            auto const hands = prc::expand_hands(e);
            for (auto const& h : hands)
            {
                auto const n = h.string();
                auto it = std::find_if(ret.begin(), ret.end(), [&n](auto& elem){ return elem.name().toStdString() == n; });
                if (it == ret.end())
                    throw std::runtime_error("should not happen: invalid hand " + n);
                it->appendSubrange(RangeInfo{QString::fromStdString(sub.name()), QColor::fromRgb(sub.rgb()), w});
            }
        }
    }
    return ret;
}

QList<RangeInfo> Range::subrangeInfo() const
{
    QList<RangeInfo> ret;

    for (auto const& sub : _range.subranges())
        ret.append(RangeInfo{QString::fromStdString(sub.name()), QColor::fromRgb(sub.rgb()), 0});

    return ret;
}
