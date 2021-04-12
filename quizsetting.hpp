#ifndef QUIZSETTING_HPP
#define QUIZSETTING_HPP

#include <QStandardItem>

class QuizSetting : public QStandardItem
{
public:
    QuizSetting(QString const& text, QVariant const& payload, QString const& type, QVariant const& value);

    QString const& settingType() const;
    QVariant const& value() const;
    QVariant const& payload() const;

    void setValue(QVariant const& v);

private:
    QString _name;
    QVariant _payload;
    QString _type;
    QVariant _value;
};

#endif // QUIZSETTING_HPP
