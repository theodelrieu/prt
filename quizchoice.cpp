#include "quizchoice.hpp"

QuizChoice::QuizChoice(QString const& text, QColor textColor): _text(text), _textColor(textColor)
{

}

QString const& QuizChoice::text() const
{
    return _text;
}

QColor QuizChoice::textColor() const
{
    return _textColor;
}
