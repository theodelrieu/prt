#ifndef QUIZCHOICE_HPP
#define QUIZCHOICE_HPP

#include <QObject>
#include <QColor>

class QuizChoice
{
    Q_GADGET
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(QColor textColor READ textColor)

public:
    QuizChoice() = default;
    QuizChoice(QString const& text, QColor textColor = "black");

    QString const& text() const;
    QColor textColor() const;

private:
    QString _text;
    QColor _textColor;
};

Q_DECLARE_METATYPE(QuizChoice)

#endif // QUIZCHOICE_HPP
