#ifndef QUIZSETTINGGROUPMODEL_HPP
#define QUIZSETTINGGROUPMODEL_HPP

#include <QStandardItemModel>

#include "quizsetting.hpp"
#include "range.hpp"

class QuizSettingGroupModel : public QStandardItemModel {
 public:
  enum Roles {
    NameRole = Qt::UserRole + 1,
    SettingsRole,
    LastRole,
  };

  explicit QuizSettingGroupModel(QObject* parent = nullptr);

  void setRange(Range const*);

  QList<RangeInfo> excludedSubranges() const;
  QString groupText(QModelIndex const&) const;
  QList<QVariant> settings(QModelIndex const&) const;

  QVariant data(QModelIndex const& idx, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

 private:
  Range const* _range;
};

#endif  // QUIZSETTINGGROUPMODEL_HPP
