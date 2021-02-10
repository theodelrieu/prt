#ifndef TREEITEM_HPP
#define TREEITEM_HPP

#include <QtCore/QList>
#include <QtCore/QVariant>

class TreeItem
{
public:
    explicit TreeItem(QVariant const& data, TreeItem *parentItem);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem *> _childItems;
    QVariant _itemData;
    TreeItem *_parentItem;
};

#endif // TREEITEM_HPP
