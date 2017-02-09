#ifndef TIMER_H
#define TIMER_H

#include <QTime>
#include <QTimer>
#include <QWidget>

class Timer : public QTimer
{
    Q_OBJECT

    public:
        Timer(QWidget *parent = 0);
		QTime *masterTime;
		int intCurrentPosition;
		int intStopPosition;

	public slots:
		void startMasterTimer();
		void stopMasterTimer();
		void resetTimer();
		void advanceTimer();

	signals:
		void signalParent(int);

};

#endif // TIMER_H
