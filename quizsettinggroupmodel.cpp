
#include "quizsettinggroupmodel.hpp"

QuizSettingGroupModel::QuizSettingGroupModel(QObject *parent)
    : QStandardItemModel(parent) {}

void QuizSettingGroupModel::setRange(Range const *range) {
  _range = range;
  beginResetModel();
  clear();
  auto root = invisibleRootItem();
  auto const subranges = _range->subrangeInfo();
  // TODO 1 setting group per row (QuizSettingGroup object)
  // if (!subranges.empty()) {
  //   QList<QStandardItem *> items;
  //   items.append(new QStandardItem("Some stuff about 100% ranges"));
  //   for (auto const &sub : qAsConst(subranges)) {
  //     items.append(new QuizSetting(sub.name(), QVariant::fromValue(sub),
  //                                  "checkbox", false));
  //   }
  //   root->appendRow(items);
  // }
  endResetModel();
}

QVariant QuizSettingGroupModel::data(QModelIndex const &idx, int role) const {
  if (!idx.isValid()) return {};
  if (role < NameRole || role >= LastRole) return {};
  switch (role) {
    case NameRole:
      return text();
    case SettingsRole:
      return settings();
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
