#ifndef QUIZSETTING_HPP
#define QUIZSETTING_HPP

#include <QStandardItem>

class QuizSetting : public QObject, public QStandardItem {
  Q_OBJECT
  Q_PROPERTY(QString type READ settingType)
  Q_PROPERTY(QVariant value READ value WRITE setValue)
  Q_PROPERTY(QString text READ text)
 public:
  QuizSetting(QString const& text, QVariant const& payload, QString const& type,
              QVariant const& value, QObject* parent = nullptr);

  QString const& settingType() const;
  QVariant const& value() const;
  QVariant const& payload() const;

  void setValue(QVariant const& v);

 private:
  QVariant _payload;
  QString _type;
  QVariant _value;
};

Q_DECLARE_METATYPE(QuizSetting)

#endif  // QUIZSETTING_HPP
