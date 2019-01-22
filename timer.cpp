#include <QApplication>
#include <QWidget>
#include <QTime>
#include <QTimer>

#include "timer.h"

Timer::Timer(QWidget *parent) : QTimer(parent)
{
	masterTime = new QTime;
	resetTimer();

    setTimerType(Qt::PreciseTimer);
	setInterval(10);
	connect(this, SIGNAL(timeout()), this, SLOT(advanceTimer()));
}

void Timer::advanceTimer() {
    //intCurrentPosition += masterTime->elapsed();
	intCurrentPosition = masterTime->elapsed() + intStopPosition;
	emit signalTimerAdvanced(intCurrentPosition);
}

void Timer::startMasterTimer() {
	if (isActive()) {
		stopMasterTimer();
	} else {
		start();
		masterTime->restart();
	}
}

void Timer::stopMasterTimer() {
    stop();
	intStopPosition = intCurrentPosition;
}

void Timer::resetTimer() {
	intCurrentPosition = 0;
	intStopPosition = 0;
}
