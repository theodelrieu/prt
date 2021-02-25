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
    QString const& name() const;
    QList<HandInfo> toHandInfo() const;

private:
    prc::range _range;
};

#endif // RANGE_HPP
