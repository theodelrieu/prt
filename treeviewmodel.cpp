#include "treeviewmodel.hpp"
#include "range.hpp"

namespace
{
QStandardItem* entryToRow(prc::folder::entry const& entry)
{
    if (auto f = boost::variant2::get_if<prc::folder>(&entry))
    {
        auto folder = new QStandardItem;
        folder->setText(QString::fromStdString(f->name()));
        for (auto const& e : f->entries())
            folder->appendRow(entryToRow(e));
        return folder;
    }
    return new Range(boost::variant2::get<prc::range>(entry));
}
}

TreeViewModel::TreeViewModel(QObject* parent)  : QStandardItemModel(parent)
{
}

QVariant TreeViewModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return {};
    if (role < NameRole || role >= LastRole)
        return {};
    auto item = itemFromIndex(idx);
    if (!item)
        return {};
    switch (role)
    {
    case NameRole:
        return item->text();
    case TypeRole:
        return dynamic_cast<Range*>(item) ? "range" : "folder";
    case IndexRole:
        return idx;
    default:
        return {};
    }
}

QPersistentModelIndex TreeViewModel::rootIndex() const
{
    return invisibleRootItem()->index();
}

QHash<int, QByteArray> TreeViewModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[TypeRole] = "type";
    names[IndexRole] = "persistentIndex";
    return names;
}

void TreeViewModel::setRoot(prc::folder const& f)
{
    beginResetModel();
    clear();
    setColumnCount(1);
    auto root = invisibleRootItem();
    for (auto const& e : f.entries())
        root->appendRow(entryToRow(e));
    endResetModel();
}
