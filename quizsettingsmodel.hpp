#ifndef QUIZSETTINGSMODEL_HPP
#define QUIZSETTINGSMODEL_HPP

#include <QStandardItemModel>
#include "quizsetting.hpp"
#include "range.hpp"

class QuizSettingsModel : public QStandardItemModel
{
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        ValueRole,
        LastRole,
    };

    explicit QuizSettingsModel(QObject *parent = nullptr);

    void setSettings(QList<QuizSetting*> const&);
    void appendSetting(QuizSetting*);

    QList<RangeInfo> excludedSubranges() const;

    QVariant data(QModelIndex const &idx, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool setData(QModelIndex const& idx, QVariant const& v, int role) override;
};

#endif // QUIZSETTINGSMODEL_HPP
