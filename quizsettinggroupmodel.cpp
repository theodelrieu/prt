
#include "quizsettinggroupmodel.hpp"

QuizSettingGroupModel::QuizSettingGroupModel(QObject *parent)
    : QStandardItemModel(parent) {}

void QuizSettingGroupModel::setRange(Range const *range) {
  _range = range;
  beginResetModel();
  clear();
  auto root = invisibleRootItem();
  auto const subranges = _range->subrangeInfo();
  if (!subranges.empty()) {
    auto group =
        new QStandardItem("Do not quiz hands which are 100% in the range");

    QList<QStandardItem *> settings;
    for (auto const &sub : qAsConst(subranges)) {
      settings.append(new QuizSetting(sub.name(), QVariant::fromValue(sub),
                                      "checkbox", false));
    }
    group->appendRow(settings);
    root->appendRow(group);
  }

  {
    auto group = new QStandardItem("Another setting group");
    QList<QStandardItem *> settings;
    for (auto const &sub : qAsConst(subranges)) {
      settings.append(new QuizSetting(sub.name(), QVariant::fromValue(sub),
                                      "checkbox", true));
    }
    group->appendRow(settings);
    root->appendRow(group);
  }
  endResetModel();
}

QVariant QuizSettingGroupModel::data(QModelIndex const &idx, int role) const {
  if (!idx.isValid()) return {};
  if (role < NameRole || role >= LastRole) return {};
  switch (role) {
    case NameRole:
      return groupText(idx);
    case SettingsRole:
      return settings(idx);
    default:
      return {};
  }
}

QHash<int, QByteArray> QuizSettingGroupModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[NameRole] = "name";
  names[SettingsRole] = "settings";
  return names;
}

QList<QVariant> QuizSettingGroupModel::settings(QModelIndex const &idx) const {
  QList<QVariant> ret;
  auto const group = itemFromIndex(idx);
  if (!group) return {};

  for (auto i = 0; i < group->columnCount(); ++i) {
    auto const item = group->child(0, i);
    ret.append(QVariant::fromValue(static_cast<QuizSetting *>(item)));
  }
  return ret;
}

QString QuizSettingGroupModel::groupText(QModelIndex const &idx) const {
  auto const group = itemFromIndex(idx);
  if (!group) return {};
  return group->text();
}

QList<RangeInfo> QuizSettingGroupModel::excludedSubranges() const {
  QList<RangeInfo> ret;
  // FIXME find item by text/type
  auto excludedSubrangesSetting = invisibleRootItem()->child(0, 0);
  for (auto i = 0; i < excludedSubrangesSetting->columnCount(); ++i) {
    auto setting =
        static_cast<QuizSetting *>(excludedSubrangesSetting->child(0, i));
    if (setting->value().value<bool>())
      ret.append(setting->payload().value<RangeInfo>());
  }
  return ret;
}
