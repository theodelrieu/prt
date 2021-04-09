#ifndef QUIZSETTING_HPP
#define QUIZSETTING_HPP

#include <QStandardItem>

class QuizSetting : public QStandardItem
{
public:
    QuizSetting(QString const& name, QString const& type, QVariant const& value);

    QString const& name() const;
    QString const& settingType() const;
    QVariant const& value() const;

    void setValue(QVariant const& v);

private:
    QString _name;
    QString _type;
    QVariant _value;
};

#endif // QUIZSETTING_HPP
