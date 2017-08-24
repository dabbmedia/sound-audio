#ifndef TIMELINE_H
#define TIMELINE_H

#include "timelinemarker.h"
#include "timelineticksegment.h"
#include "timer.h"
#include "track.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLinkedList>
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
		QLinkedList<Track *> trackList;
		QGraphicsScene scene;
		Timer *masterTimer;
		int intTickInterval;
		int intCurrentPosition;
		qreal realScale;

	signals:
		void signalDisplay();
		void signalTimerStart();
		void signalTimerStop();
		void signalTimerReset();
		void signalTrackAdded();

	public slots :
		void zoomIn();
		void zoomOut();
		void startMainTimer();
		void stopMainTimer();
		void resetMainTimer();
		void advanceTimeline(int);
		void addTrack();

	protected:
		void createTicks();
};

#endif // TIMELINE_H
