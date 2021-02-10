#ifndef RANGELOADER_HPP
#define RANGELOADER_HPP

#include <QObject>
#include <QString>

#include <prc/folder.hpp>
#include "treemodel.hpp"

class RangeLoader : public QObject
{
    Q_OBJECT
public:
    explicit RangeLoader(TreeModel* tree, QObject *parent = nullptr);

public slots:
    void parseEquilab(QString const& fullpath);

signals:
    void parseStarted();
    void parseEnded(bool success);

private:
    TreeModel* _tree;
};

#endif // RANGELOADER_HPP
