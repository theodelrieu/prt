#ifndef RANGEINFO_HPP
#define RANGEINFO_HPP

#include <QtCore/QString>
#include <QObject>
#include <QColor>

// TODO rename HandRangInfo
class RangeInfo
{
    Q_GADGET
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QColor color READ color)
    Q_PROPERTY(double weight READ weight)
public:
    RangeInfo() = default;
    RangeInfo(QString const& name, QColor color, double weight);

    QString const& name() const;
    QColor color() const;
    double weight() const;

private:
    QString _name;
    QColor _color;
    double _weight;
};

bool operator==(RangeInfo const&, RangeInfo const&);
bool operator!=(RangeInfo const&, RangeInfo const&);

Q_DECLARE_METATYPE(RangeInfo)

#endif // RANGEINFO_HPP
