#ifndef RANGE_HPP
#define RANGE_HPP

#include <QStandardItem>
#include <QObject>

#include "handinfo.hpp"

#include <prc/range.hpp>

class Range : public QObject, public QStandardItem
{
    Q_OBJECT
public:
    Range(prc::range const& range, QObject* parent = nullptr);

    int type() const override;
    // Post-condition: result is sorted by index (AA > A2s > AKo > 22)
    QList<HandInfo> parentRangeInfo() const;
    QList<HandInfo> subrangesInfo() const;

private:
    prc::range _range;
};

#endif // RANGE_HPP
