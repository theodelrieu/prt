#include "rangedisplayer.hpp"
#include "range.hpp"

#include <iostream>

RangeDisplayer::RangeDisplayer(TreeViewModel* treeView, QObject *parent) : QStandardItemModel(parent), _treeView(treeView), _handInfo(emptyHandInfo())
{
    auto root = invisibleRootItem();
    for (auto const& elem : _handInfo)
        root->appendRow(new HandInfo(elem));
}

QVariant RangeDisplayer::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || role != Qt::DisplayRole)
        return {};
    auto item = itemFromIndex(idx);
    if (!item)
        return {};
    return item->text();
}

void RangeDisplayer::setRange(QModelIndex const& idx)
{
    if (idx == _lastIndex || !idx.isValid())
        return;
    auto item = _treeView->itemFromIndex(idx);
    if (item->type() != QStandardItem::ItemType::UserType)
        return;
    auto range = static_cast<Range*>(item);
    _lastIndex = idx;
    _handInfo = range->toHandInfo();
    std::cout << "Loaded " << range->text().toStdString() << std::endl;
}
