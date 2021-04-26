#include "quizsetting.hpp"

QuizSetting::QuizSetting(QString const& text, QVariant const& payload, QString const& type, QVariant const& value, QObject* parent): QObject(parent), QStandardItem(), _payload(payload), _type(type), _value(value)
{
    setText(text);
}

QString const& QuizSetting::settingType() const {
    return _type;
}

QVariant const& QuizSetting::value() const {
    return _value;
}

QVariant const& QuizSetting::payload() const {
    return _payload;
}

void QuizSetting::setValue(QVariant const& v) {
    _value = v;
}
