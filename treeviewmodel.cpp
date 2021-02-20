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
