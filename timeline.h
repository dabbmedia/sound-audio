#ifndef TIMELINE_H
#define TIMELINE_H

#include "timelinemarker.h"
#include "timelineticksegment.h"
#include "timer.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QThread>
#include <QWidget>

class Timeline : public QGraphicsView
{
    Q_OBJECT
	public:
		explicit Timeline(QWidget *parent = 0);
		Timeline::~Timeline();
		void setCurrentPosition(int);
		QWidget *widgetTimeline;
		QThread timerThread;
		TimelineMarker *timelineMarker;
		TimelineTickSegment *tickSegment;
		int intTickInterval;
		int intCurrentPosition;
		qreal realScale;

	signals:
		void signalDisplay(int intPos);
		void signalTimerStart();
		void signalTimerStop();
		void signalTimerReset();

	public slots :
		void zoomIn();
		void zoomOut();
		void startMainTimer();
		void stopMainTimer();
		void resetMainTimer();
		void advanceTimeline(int);

	protected:
		void createTicks();
		Timer *masterTimer;
		QGraphicsScene scene;
};

#endif // TIMELINE_H
