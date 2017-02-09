#include "timelineticksegment.h"

#include <QFont>
#include <QGraphicsLinearLayout>
#include <QGraphicsLineItem>
#include <QGraphicsWidget>
#include <QPainter>
#include <QPointF>
#include <QStringBuilder>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

TimelineTickSegment::TimelineTickSegment() : QGraphicsWidget()
{
	flFramesPerSecond = 25;
	intWidth = flFramesPerSecond * 60 * 60;
	setMinimumSize(intWidth, 24);
	setMaximumSize(intWidth, 24);
}


TimelineTickSegment::~TimelineTickSegment()
{
}

QRectF TimelineTickSegment::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
		intWidth + penWidth, intWidth + penWidth);
}

void TimelineTickSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	//option->styleObject();

	//markers for 3 hours
	// 1000ms * 60s * 60m * 3h
	//int msInterval = 2;
	//int intHeightMs = 3; // ms
	int intHeightFrame = 4; // ms
	int intHeightS = 6; //1000 (s)
	int intHeightM = 9; //60000 (m)
	int intHeightH = 12; //3600000 (h)

	/*int intHeightMeasure = 10;
	int intHeightQuarter = 8;
	int intHeightEighth = 6;
	int intHeightSixteenth = 4;
	int intHeightThirtySecond = 2;*/

	float flPixelRatio = (1000 / flFramesPerSecond); //1 frame = 1 px
	float flMinutesX = 0;
	float flSecondsX = 0;
	float flFrameX = 0;

	QPen pen(QColor("#CCCCCC"), 0.5, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
	painter->setFont(QFont("Helvetica", 6));

	for (int i = 0; i < 60; i++) { //minutes
		//qDebug() << "starting minutes loop: i = " << i;
		
		flMinutesX = i * (60 * flFramesPerSecond);
		painter->drawLine(flMinutesX, (12 - intHeightM), flMinutesX, 12); //minutes
		QString strLabelM = "m";
		strLabelM.prepend(QString::number(i));
		painter->drawText(QPointF(flMinutesX, -4), strLabelM, 8, 1);

		for (int j = 0; j < 60; j++) { //seconds
			//qDebug() << "starting seconds loop: j = " << j;
			flSecondsX = flMinutesX + (j * flFramesPerSecond);
			QPointF pfStartS = QPointF(flSecondsX, (12 - intHeightS));
			QPointF pfEndS = QPointF(flSecondsX, 12);
			painter->drawLine(pfStartS, pfEndS); //seconds

			//pen.setWidth((1 / flFramesPerSecond) / 2);
			//painter->setPen(pen);

			//for (int k = 0; k < flFramesPerSecond; k++) { //frames
			//	flFrameX = j + k;
			//	qDebug() << "starting frames loop: k = " << k << "flFrameX = " << flFrameX;
			//	painter->drawLine(flFrameX, (12 - intHeightFrame), flFrameX, 12); //frames
			/*QPointF *pfStart = new QPointF(flFrameX, (12 - intHeightFrame));
			QPointF *pfEnd = new QPointF(flFrameX, 12);*/
			//	painter->drawLine(pfStart, pfEnd //frames
			//}
		}
	}
	
	painter->drawLine(intWidth, (12 - intHeightH), intWidth, 12);
}