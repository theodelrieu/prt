#include "quizsettingsmodel.hpp"

QuizSettingsModel::QuizSettingsModel(QObject *parent) : QStandardItemModel(parent)
{
}

void QuizSettingsModel::appendSetting(QuizSetting *setting)
{
    invisibleRootItem()->appendRow(setting);
}

void QuizSettingsModel::setSettings(QList<QuizSetting*> const& settings)
{
    beginResetModel();
    clear();
    auto root = invisibleRootItem();
    for (auto const& setting : qAsConst(settings))
        root->appendRow(setting);
    endResetModel();
}

QVariant QuizSettingsModel::data(QModelIndex const &idx, int role) const
{
    if (!idx.isValid())
        return {};
    if (role < NameRole || role >= LastRole)
        return {};
    auto item = dynamic_cast<QuizSetting*>(itemFromIndex(idx));
    if (!item)
        return {};
    switch (role)
    {
    case NameRole:
        return item->name();
    case TypeRole:
         return item->settingType();
    case ValueRole:
        return item->value();
    default:
        return {};
    }
}

bool QuizSettingsModel::setData(QModelIndex const &idx, QVariant const &v, int role)
{
    if (role != ValueRole)
        return false;
    auto item = dynamic_cast<QuizSetting*>(itemFromIndex(idx));
    if (!item)
        return false;
    item->setValue(v);
    return true;
}

QHash<int, QByteArray> QuizSettingsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[TypeRole] = "type";
    names[ValueRole] = "value";
    return names;
}

QList<RangeInfo> QuizSettingsModel::excludedSubranges() const
{
  QList<RangeInfo> ret;
  for (auto i = 0; i < rowCount(); ++i)
  {
      auto setting = static_cast<QuizSetting*>(item(i, 0));
      // TODO finish it

  }
  return ret;
}
