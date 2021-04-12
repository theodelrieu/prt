#ifndef QUIZER_HPP
#define QUIZER_HPP

#include <QObject>

#include <tuple>
#include <random>
#include <vector>
#include "rangedisplayer.hpp"
#include "quizchoice.hpp"

class Quizer : public QObject
{
    Q_OBJECT
public:
    enum class QuizType {
        InBaseRange,
        InSubrange,
        MostPlayed,
    };

    // TODO stop passing RangeDisplayer, add a setRange and connect objects in main
    explicit Quizer(RangeDisplayer const*, QObject *parent = nullptr);

public slots:
    void start();
    void next();
    void stop();
    void answer(int buttonIndex);

signals:
    void newQuiz(int handIdx, QString const& question, QList<QuizChoice> const& choices);
    void answered(QString const& result);

private:
    void nextQuiz();
    void nextInBaseRangeQuiz(HandInfo const*, int);
    void nextInSubrangeQuiz(HandInfo const*, int);
    void nextMostPlayedQuiz(HandInfo const*, int);
    std::tuple<QuizType, HandInfo const*, int> nextQuizParams();

    RangeDisplayer const* _displayer;
    std::mt19937 _rng;
    std::vector<HandInfo> _quizHands;
    int _correctAnswerButtonIndex{};
    int _succeededAttempts{};
    int _totalAttempts{};
};

#endif // QUIZER_HPP
