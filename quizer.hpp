#ifndef QUIZER_HPP
#define QUIZER_HPP

#include <QObject>

class Quizer : public QObject
{
    Q_OBJECT
public:
    explicit Quizer(QObject *parent = nullptr);

public slots:
    void start();
    void stop();

signals:
    void quizStarted();
    void quizStopped();
};

#endif // QUIZER_HPP
