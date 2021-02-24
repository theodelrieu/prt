#include "rangedisplayer.hpp"
#include "range.hpp"

#include <iostream>

RangeDisplayer::RangeDisplayer(TreeViewModel* treeView, QObject *parent) : QStandardItemModel(parent), _treeView(treeView), _handInfo(emptyHandInfo())
{
    auto root = invisibleRootItem();
    for (auto const& elem : qAsConst(_handInfo))
        root->appendRow(new HandInfo(elem));
}

QVariant RangeDisplayer::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return {};
    if (role < NameRole || role > ParentRangeRole)
        return {};
    auto item = itemFromIndex(idx);
    if (!item)
        return {};
    auto info = static_cast<HandInfo*>(item);
    switch (role)
    {
    case NameRole:
        return info->name();
    case ParentRangeRole:
    {
        auto const& ranges = info->ranges();
        if (ranges.empty())
            return QVariant::fromValue(RangeInfo{});
        return QVariant::fromValue(ranges.front());
    }
    default:
        return {};
    }
}

QHash<int, QByteArray> RangeDisplayer::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[ParentRangeRole] = "parentRange";
    return names;
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
    _handInfo = range->parentRangeInfo();
    beginResetModel();
    clear();
    auto root = invisibleRootItem();
    for (auto const& elem : qAsConst(_handInfo))
        root->appendRow(new HandInfo(elem));
    endResetModel();
    std::cout << "Loaded " << range->text().toStdString() << std::endl;
}
