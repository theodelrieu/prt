#include "treemodel.hpp"

#include <iostream>

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    _rootItem = new TreeItem(QString("root"), nullptr);
}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

QModelIndex TreeModel::index(int row, int column, QModelIndex const &parent) const
{
    std::cout << "index called" << std::endl;
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(QModelIndex const &index) const
{
    std::cout << "parent called" << std::endl;
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(QModelIndex const &parent) const
{
    std::cout << "rowCount called" << std::endl;
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());


    auto count =  parentItem->childCount();
    std::cout << "nbChildren = " << count << std::endl;
    return count;
}

int TreeModel::columnCount(QModelIndex const &parent) const
{
    std::cout << "columnCount called" << std::endl;
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    auto count =  _rootItem->columnCount();
    std::cout << "columnCount = " << count << std::endl;
    return count;
}

QVariant TreeModel::data(QModelIndex const &index, int role) const
{
    std::cout << "data called" << std::endl;
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(QModelIndex const &index) const
{
    std::cout << "flags called" << std::endl;
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    std::cout << "headerData called" << std::endl;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}

void TreeModel::setRoot(const prc::folder &f) {
    std::cout << "setRoot called" << std::endl;
    std::cout << "root has " << f.entries().size() << "entries" << std::endl;
    beginResetModel();
    std::cout << "after beginresetmodel" << std::endl;
    auto newRoot = new TreeItem(QString("root"), nullptr);
    auto sub = new TreeItem(QString("new item"), newRoot);
    newRoot->appendChild(sub);
    delete _rootItem;
    _rootItem = newRoot;
    endResetModel();
    std::cout << "after resetmodel" << std::endl;
}
