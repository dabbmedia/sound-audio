#include "trackcontrolstimeline.h"

#include <QFont>
#include <QGraphicsLineItem>
#include <QGraphicsWidget>
#include <QPainter>
#include <QPointF>
#include <QStyleOptionGraphicsItem>
#include <QtDebug>

TrackControlsTimeline::TrackControlsTimeline()
	: QGraphicsWidget()
{
	intWidth = 240;
	setMinimumSize(intWidth, 24);
	setMaximumSize(intWidth, 24);
}

TrackControlsTimeline::~TrackControlsTimeline()
{
}

QRectF TrackControlsTimeline::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
		intWidth + penWidth, intWidth + penWidth);
}

void TrackControlsTimeline::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(QColor("#CCCCCC"), 0.5, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
	painter->setFont(QFont("Helvetica", 6));
	//painter->drawText(QPointF(flMinutesX, -4), strLabelM, 8, 1);

	painter->drawLine(intWidth, (12 - 24), intWidth, 12);
}
