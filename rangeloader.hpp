#ifndef RANGELOADER_HPP
#define RANGELOADER_HPP

#include <QtCore/QObject>
#include <QtCore/QString>

#include <prc/folder.hpp>
#include "treeviewmodel.hpp"

class RangeLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool hasLocalRanges READ hasLocalRanges NOTIFY hasLocalRangesChanged)
public:
    explicit RangeLoader(TreeViewModel* tree, QObject *parent = nullptr);

    bool hasLocalRanges() const;

public slots:
    void parseEquilab(QString const& fullpath);
    void parsePio(QString const& fullpath);

signals:
    void parseStarted();
    void hasLocalRangesChanged();
    void parseEnded(bool success);

private:
    void writeLocalRanges();

    prc::folder _root;
    TreeViewModel* _tree;
    bool _hasLocalRanges;
};

#endif // RANGELOADER_HPP
