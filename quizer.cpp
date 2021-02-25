#include "quizer.hpp"

Quizer::Quizer(QObject *parent) : QObject(parent)
{

}

void Quizer::start()
{
    emit quizStarted();
}

void Quizer::stop()
{
    emit quizStopped();
}
