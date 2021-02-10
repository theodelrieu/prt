#include "treeitem.hpp"

#include <iostream>

TreeItem::TreeItem(QVariant const &data, TreeItem *parent)
    : _itemData(data), _parentItem(parent)
{}

TreeItem::~TreeItem(){
    qDeleteAll(_childItems);
}

void TreeItem::appendChild(TreeItem *item){
    _childItems.append(item);
}

TreeItem* TreeItem::child(int row)
{
    std::cout << "TreeItem::child called with row = " << row <<std::endl;
    if (row < 0 || row >= _childItems.size())
        return nullptr;
    return _childItems.at(row);
}

int TreeItem::childCount() const
{

    std::cout << "TreeItem::childCount called" << std::endl;
    return _childItems.count();
}

int TreeItem::row() const
{
    std::cout << "TreeItem::row called" << std::endl;
    if (_parentItem)
        return _parentItem->_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    std::cout << "TreeItem::columnCount called" << std::endl;
    return 1;
}

QVariant TreeItem::data(int column) const
{
    std::cout << "TreeItem::data called with column " << column << std::endl;
    if (column != 1)
        return QVariant();
    return _itemData;
}

TreeItem *TreeItem::parentItem()
{
    std::cout << "TreeItem::parentItem called" << std::endl;
    return _parentItem;
}
