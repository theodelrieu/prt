#include "quizsetting.hpp"

QuizSetting::QuizSetting(QString const& name, QString const& type, QVariant const& value): QStandardItem(), _name(name), _type(type), _value(value)
{

}

QString const& QuizSetting::name() const {
    return _name;
}

QString const& QuizSetting::settingType() const {
    return _type;
}

QVariant const& QuizSetting::value() const {
    return _value;
}

void QuizSetting::setValue(QVariant const& v) {
    _value = v;
}
