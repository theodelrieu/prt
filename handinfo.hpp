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
    HandInfo(QString const& name, QList<RangeInfo> const& ranges);

    QString const& name() const;
    QList<RangeInfo> const& ranges() const;

    void appendRange(RangeInfo);

private:
    QString _name;
    QList<RangeInfo> _ranges;
};

QList<HandInfo> emptyHandInfo();

#endif // HANDINFO_HPP
