#include "timer.h"

#include <QWidget>
#include <QtDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QLineEdit>

Timer::Timer(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(10, 2, 0, 0);

    lcdTimer = new QLCDNumber;
    lcdTimer->setSegmentStyle(QLCDNumber::Flat);
    lcdTimer->setDigitCount(12);

    hbox->addWidget(lcdTimer, 0, Qt::AlignLeft | Qt::AlignTop);

    lcdTimer->display("00:00:00.000");

    masterTime = new QTime;

    masterTimer = new QTimer(this);
    masterTimer->setTimerType(Qt::PreciseTimer);
    masterTimer->setInterval( 50 );
    connect(masterTimer, SIGNAL(timeout()), this, SLOT(advanceTimeline()));
}

void Timer::advanceTimeline() {
//    qDebug() << "ax name: " << editTimerText->accessibleName();
    QTime t = QTime(0, 0, 0, 0).addMSecs(masterTime->elapsed());
    QString stringElapsed = t.toString("hh:mm:ss.zzz");
    lcdTimer->display(stringElapsed);
}

void Timer::startMasterTimer() {
//    startTimer(1);
    masterTimer->start();
    masterTime->restart();
}

void Timer::stopMasterTimer() {
    masterTimer->stop();
}
