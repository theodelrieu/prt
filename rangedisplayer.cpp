#include "rangedisplayer.hpp"
#include "range.hpp"
#include "quizsetting.hpp"

RangeDisplayer::RangeDisplayer(TreeViewModel* treeView, QuizSettingsModel* settings, QObject *parent) : QStandardItemModel(parent), _treeView(treeView), _handInfo(emptyHandInfo()), _quizSettings(settings)
{
    auto root = invisibleRootItem();
    for (auto const& elem : qAsConst(_handInfo))
        root->appendRow(new HandInfo(elem));
}

RangeDisplayer::~RangeDisplayer()
{
    delete _quizSettings;
}

QList<HandInfo> const& RangeDisplayer::handInfo() const
{
    return _handInfo;
}

Range const* RangeDisplayer::currentRange() const
{
    return _currentRange;
}

QVariant RangeDisplayer::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid())
        return {};
    if (role < NameRole || role >= LastRole)
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
        return QVariant::fromValue(info->parentRange());
    case SubrangesRole:
        return QVariant::fromValue(info->subranges());
    default:
        return {};
    }
}

QHash<int, QByteArray> RangeDisplayer::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[ParentRangeRole] = "parentRange";
    names[SubrangesRole] = "subranges";
    return names;
}

void RangeDisplayer::setRange(QModelIndex const& idx)
{
    if (idx == _lastTreeIndex || !idx.isValid())
        return;
    auto item = _treeView->itemFromIndex(idx);
    if (item->type() != QStandardItem::ItemType::UserType)
        return;
    _currentRange = static_cast<Range*>(item);
    _lastTreeIndex = idx;
    _handInfo = _currentRange->toHandInfo();
    beginResetModel();
    clear();
    auto root = invisibleRootItem();
    for (auto const& elem : qAsConst(_handInfo))
        root->appendRow(new HandInfo(elem));
    _quizSettings->setRange(_currentRange);

    endResetModel();
    emit rangeLoaded(_currentRange->name());
}

QuizSettingsModel const* RangeDisplayer::quizSettings() const
{
    return _quizSettings;
}
