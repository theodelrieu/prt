#ifndef RANGEFOLDER_HPP
#define RANGEFOLDER_HPP

#include <QObject>

#include <prc/folder.hpp>

class RangeFolder : public QObject
{
    Q_OBJECT
public:
    explicit RangeFolder(QObject *parent = nullptr, prc::folder);

signals:

private:
    prc::folder _root;
};

#endif // RANGEFOLDER_HPP
