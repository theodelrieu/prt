#ifndef RANGELOADER_HPP
#define RANGELOADER_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFutureWatcher>

#include <prc/folder.hpp>
#include "treeviewmodel.hpp"

class RangeLoader : public QObject
{
    Q_OBJECT
public:
    explicit RangeLoader(TreeViewModel* tree, QObject *parent = nullptr);

public slots:
    void parseEquilab(QString const& fullpath);
    void parsePio(QString const& fullpath);

signals:
    void parseStarted();
    void parseEnded(bool success);

private slots:
    void handleFinished();
    void handleCanceled();

private:
    QFutureWatcher<prc::folder> _watcher;
    prc::folder _root;
    TreeViewModel* _tree;
};

#endif // RANGELOADER_HPP
