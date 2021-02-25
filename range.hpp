#ifndef RANGE_HPP
#define RANGE_HPP

#include <QStandardItem>
#include <QObject>

#include "handinfo.hpp"
#include "rangeinfo.hpp"

#include <prc/range.hpp>

class Range : public QObject, public QStandardItem
{
    Q_OBJECT
public:
    Range(prc::range const& range, QObject* parent = nullptr);

    int type() const override;
    QString name() const;
    // TODO RangeInfo = HandRangeInfo without weight
    QList<RangeInfo> subrangeInfo() const;
    QList<HandInfo> toHandInfo() const;

private:
    prc::range _range;
};

#endif // RANGE_HPP
