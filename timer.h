#ifndef TIMER_H
#define TIMER_H

#include <QLabel>
#include <QLCDNumber>
#include <QLineEdit>
#include <QObject>
#include <QTime>
#include <QTimer>
#include <QWidget>

class Timer : public QWidget
{
    Q_OBJECT

    public:
        Timer(QWidget *parent = 0);
        QLCDNumber *lcdTimer;
        void startMasterTimer();
        void stopMasterTimer();

    protected:
        QTime *masterTime;
        QTimer *masterTimer;
//        void timerEvent(QTimerEvent *e);

    protected slots:
        void advanceTimeline();

};

#endif // TIMER_H
