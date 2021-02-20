#ifndef TREEVIEWMODEL_HPP
#define TREEVIEWMODEL_HPP

#include <QStandardItemModel>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT
public:
    TreeViewModel(QObject* parent = nullptr);
};

#endif // TREEVIEWMODEL_HPP
