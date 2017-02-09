#include "timeline.h"
#include "timelinemarker.h"
#include "timelineticksegment.h"
#include "timer.h"

#include <QGraphicsView>
#include <QPointF>
#include <QScrollBar>
#include <QSplitter>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>
#include <QtDebug>

Timeline::Timeline(QWidget *parent) : QGraphicsView(parent)
{
	tickSegment = new TimelineTickSegment();

	//scene(-350, -350, 700, 700);
	scene.setSceneRect(0, -200, tickSegment->intWidth, 400);

	//setViewport(window.widgetTlEditor);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setScene(&scene);
	setAlignment(Qt::AlignTop);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	realScale = 1.0;
	scale(realScale, 1.0);

	createTicks();

	intCurrentPosition = 0;

	timelineMarker = new TimelineMarker;
	timelineMarker->setPos(intCurrentPosition, -174);
	timelineMarker->setScale(1.0);
	scene.addItem(timelineMarker);
	//show();

	masterTimer = new Timer;
	masterTimer->moveToThread(&timerThread);
	connect(&timerThread, &QThread::finished, masterTimer, &QObject::deleteLater);
	connect(this, &Timeline::signalTimerStart, masterTimer, &Timer::startMasterTimer);
	connect(this, &Timeline::signalTimerStop, masterTimer, &Timer::stopMasterTimer);
	connect(this, &Timeline::signalTimerReset, masterTimer, &Timer::resetTimer);
	connect(masterTimer, SIGNAL(signalParent(int)), this, SLOT(advanceTimeline(int)));
	timerThread.start();
}

Timeline::~Timeline() {
	timerThread.quit();
	timerThread.wait();
}

void Timeline::createTicks() {
	//TimelineTickSegment tickSegment;
	/*for (int i = 0; i < 5; i++) {
		TimelineTickSegment *tickSegment = new TimelineTickSegment();
		tickSegment->setPos(i * (60 * 60), -188);
		scene.addItem(tickSegment);
	}*/
	tickSegment->setPos(0, -176);

	scene.addRect(0, -188, tickSegment->intWidth, 24, QPen("#333333"), QBrush("#333333"));

	scene.addItem(tickSegment);
}

void Timeline::zoomIn() {
	realScale = realScale * 1.2;
	scale(1.2, 1.0);
	timelineMarker->setScale(1.0);
	qDebug() << "zoom in: " << realScale;
	if (realScale > 1.44) {
		qDebug() << "hide stuff";
	}
}

void Timeline::zoomOut() {
	realScale = realScale / 1.2;
	scale(1 / 1.2, 1.0);
	timelineMarker->setScale(1.0);
	qDebug() << "zoom out: " << realScale;
	if (realScale < 1.44) {
		qDebug() << "do stuff";
	}
}

void Timeline::advanceTimeline(int intPos) {
	setCurrentPosition(intPos);
}

void Timeline::setCurrentPosition(int intPos) {
	intCurrentPosition = intPos;
	timelineMarker->setPos(intCurrentPosition / (1000 / tickSegment->flFramesPerSecond), -174);
	emit signalDisplay(intPos);
}

void Timeline::startMainTimer() {
	emit signalTimerStart();
}

void Timeline::stopMainTimer() {
	emit signalTimerStop();
}

void Timeline::resetMainTimer() {
	setCurrentPosition(0);
	emit signalTimerReset();
}
