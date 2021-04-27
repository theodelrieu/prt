
#include "quizsettinggroupmodel.hpp"

#include <iostream>

QuizSettingGroupModel::QuizSettingGroupModel(QObject *parent)
    : QStandardItemModel(parent) {}

void QuizSettingGroupModel::setRange(Range const *range) {
  _range = range;
  beginResetModel();
  clear();
  auto root = invisibleRootItem();
  auto const subranges = _range->subrangeInfo();
  if (!subranges.empty()) {
    QList<QStandardItem *> items;
    items.append(new QStandardItem("Some stuff about 100% ranges"));
    for (auto const &sub : qAsConst(subranges)) {
      items.append(new QuizSetting(sub.name(), QVariant::fromValue(sub),
                                   "checkbox", false));
    }
    root->appendRow(items);

    std::cout << "root.columnCount: " << root->columnCount() << std::endl;
    std::cout << "root.rowCount: " << root->rowCount() << std::endl;
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

  std::cout << "columnCount: " << group->columnCount() << std::endl;
  for (auto i = 1; i < group->columnCount(); ++i) {
    auto const item = itemFromIndex(index(idx.row(), i));
    ret.append(QVariant::fromValue(static_cast<QuizSetting *>(item)));
  }
  return ret;
}

QString QuizSettingGroupModel::groupText(QModelIndex const &idx) const {
  auto const group = itemFromIndex(idx);
  std::cout << "idx.row: " << idx.row() << " column: " << idx.column()
            << std::endl;
  if (!group) return {};
  return itemFromIndex(index(idx.row(), 0))->text();
}

QList<RangeInfo> QuizSettingGroupModel::excludedSubranges() const {
  // FIXME
  return {};
  // QList<RangeInfo> ret;
  // for (auto i = 0; i < rowCount(); ++i) {
  //   auto setting = static_cast<QuizSetting *>(item(i, 0));
  //   if (setting->value().value<bool>())
  //     ret.append(setting->payload().value<RangeInfo>());
  // }
  // return ret;
}
