#ifndef HANDINFO_HPP
#define HANDINFO_HPP

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QStandardItem>

#include "rangeinfo.hpp"

class HandInfo : public QStandardItem
{
public:
    HandInfo(QString const& name, QVector<RangeInfo> const& ranges);

    QVariant data(int role) const override;
    QString const& name() const;
    void appendRange(RangeInfo const&);

private:
    QString _name;
    QVector<RangeInfo> _ranges;
};

QVector<HandInfo> emptyHandInfo();

#endif // HANDINFO_HPP
