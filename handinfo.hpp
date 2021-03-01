#ifndef HANDINFO_HPP
#define HANDINFO_HPP

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QStandardItem>

#include "rangeinfo.hpp"

class HandInfo : public QStandardItem
{
public:
    HandInfo() = default;
    HandInfo(QString const& name, RangeInfo const& parentRange, QList<RangeInfo> const& subranges = {});

    QString const& name() const;
    RangeInfo const& parentRange() const;
    QList<RangeInfo> const& subranges() const;

    void setParentRange(RangeInfo const&);
    void appendSubrange(RangeInfo const&);

private:
    QString _name;
    RangeInfo _parentRange;
    QList<RangeInfo> _subranges;
};

QList<HandInfo> emptyHandInfo();

#endif // HANDINFO_HPP
