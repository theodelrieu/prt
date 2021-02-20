#ifndef TREEVIEWMODEL_HPP
#define TREEVIEWMODEL_HPP

#include <QStandardItemModel>

#include <prc/folder.hpp>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TreeViewModel(QObject* parent = nullptr);

public slots:
    void setRoot(prc::folder const&);
};

#endif // TREEVIEWMODEL_HPP
