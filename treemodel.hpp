#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP

#include <QAbstractItemModel>
#include <QObject>

#include "treeitem.hpp"

#include <prc/folder.hpp>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void setRoot(prc::folder const&);

private:
    TreeItem *_rootItem;
};

#endif // TREEMODEL_HPP
