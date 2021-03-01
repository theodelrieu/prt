#ifndef QUIZER_HPP
#define QUIZER_HPP

#include <QObject>

#include <random>
#include "rangedisplayer.hpp"

class Quizer : public QObject
{
    Q_OBJECT
public:
    explicit Quizer(RangeDisplayer*, QObject *parent = nullptr);

public slots:
    void start();
    void next();
    void stop();
    void answer(bool);

signals:
    void newQuiz(int handIdx, QString const& question);
    void answered(QString const& result);

private:
    void nextQuiz();

    RangeDisplayer* _displayer;
    std::mt19937 _rng;
    bool _answer;
    int _succeededAttempts{};
    int _totalAttempts{};
};

#endif // QUIZER_HPP
