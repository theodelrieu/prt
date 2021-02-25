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
    void stop();

signals:
    void newQuiz(int handIdx, RangeInfo const&);

private:
    RangeDisplayer* _displayer;
    int _succeededAttempts{};
    int _totalAttempts{};
    std::mt19937 _rng;
};

#endif // QUIZER_HPP
