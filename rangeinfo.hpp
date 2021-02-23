#ifndef RANGEINFO_HPP
#define RANGEINFO_HPP

#include <QtCore/QString>
#include <QStandardItem>
#include <QColor>

class RangeInfo : public QStandardItem
{
public:
    RangeInfo(QString const& name, QColor color, double weight);

    QString const& name() const;
    QColor color() const;
    double weight() const;

private:
    QString _name;
    QColor _color;
    double _weight;
};

#endif // RANGEINFO_HPP
