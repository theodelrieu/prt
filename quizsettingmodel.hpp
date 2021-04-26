#ifndef QUIZSETTINGMODEL_HPP
#define QUIZSETTINGMODEL_HPP

#include <QStandardItemModel>

#include "quizsetting.hpp"
#include "range.hpp"

class QuizSettingModel : public QStandardItemModel {
 public:
  enum Roles {
    NameRole = Qt::UserRole + 1,
    TypeRole,
    ValueRole,
    LastRole,
  };

  explicit QuizSettingModel(QObject* parent = nullptr);

  void setRange(Range const*);

  QList<RangeInfo> excludedSubranges() const;

  QVariant data(QModelIndex const& idx, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  bool setData(QModelIndex const& idx, QVariant const& v, int role) override;

 private:
  Range const* _range;
};

#endif  // QUIZSETTINGMODEL_HPP
