#include "quizsettingsmodel.hpp"
#include <iostream>

namespace
{
class QuizSetting : public QStandardItem
{
public:
    QuizSetting(QString const& name, QString const& type, QVariant const& value): QStandardItem(), _name(name), _type(type), _value(value)
    {

    }

    QString const& name() const {
        return _name;
    }

    QString const& settingType() const {
        return _type;
    }

    QVariant const& value() const {
        return _value;
    }

    void setValue(QVariant const& v) {
        _value = v;
    }

private:
    QString _name;
    QString _type;
    QVariant _value;
};
}

QuizSettingsModel::QuizSettingsModel(QObject *parent) : QStandardItemModel(parent)
{
    auto root = invisibleRootItem();
    root->appendRow(new QuizSetting("test setting 1", "checkbox", true));
    root->appendRow(new QuizSetting("test setting 2", "checkbox", true));
    root->appendRow(new QuizSetting("test setting 3", "checkbox", false));
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
