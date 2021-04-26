
#include "quizsettingmodel.hpp"

QuizSettingModel::QuizSettingModel(QObject *parent)
    : QStandardItemModel(parent) {}

void QuizSettingModel::setRange(Range const *range) {
  _range = range;
  beginResetModel();
  clear();
  auto root = invisibleRootItem();
  auto const subranges = _range->subrangeInfo();
  if (!subranges.empty()) {
    // TODO 1 setting group per row (QuizSettingGroup object?)
    for (auto const &sub : qAsConst(subranges))
      root->appendRow(new QuizSetting(sub.name(), QVariant::fromValue(sub),
                                      "checkbox", false));
  }
  endResetModel();
}

QVariant QuizSettingModel::data(QModelIndex const &idx, int role) const {
  if (!idx.isValid()) return {};
  if (role < NameRole || role >= LastRole) return {};
  auto item = dynamic_cast<QuizSetting *>(itemFromIndex(idx));
  if (!item) return {};
  switch (role) {
    case NameRole:
      return item->text();
    case TypeRole:
      return item->settingType();
    case ValueRole:
      return item->value();
    default:
      return {};
  }
}

bool QuizSettingModel::setData(QModelIndex const &idx, QVariant const &v,
                               int role) {
  if (role != ValueRole) return false;
  auto item = dynamic_cast<QuizSetting *>(itemFromIndex(idx));
  if (!item) return false;
  item->setValue(v);
  return true;
}

QHash<int, QByteArray> QuizSettingModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[NameRole] = "name";
  names[TypeRole] = "type";
  names[ValueRole] = "value";
  return names;
}

QList<RangeInfo> QuizSettingModel::excludedSubranges() const {
  QList<RangeInfo> ret;
  for (auto i = 0; i < rowCount(); ++i) {
    auto setting = static_cast<QuizSetting *>(item(i, 0));
    if (setting->value().value<bool>())
      ret.append(setting->payload().value<RangeInfo>());
  }
  return ret;
}
