#ifndef RANGELOADER_HPP
#define RANGELOADER_HPP

#include <QObject>
#include <QString>

#include <prc/folder.hpp>
#include "treeviewmodel.hpp"

class RangeLoader : public QObject
{
    Q_OBJECT
public:
    explicit RangeLoader(TreeViewModel* tree, QObject *parent = nullptr);

public slots:
    void parseEquilab(QString const& fullpath);

signals:
    void parseStarted();
    void parseEnded(bool success);

private:
    TreeViewModel* _tree;
};

#endif // RANGELOADER_HPP
