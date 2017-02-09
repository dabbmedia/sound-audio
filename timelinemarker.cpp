#include "timelinemarker.h"

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

TimelineMarker::TimelineMarker()
{

}


TimelineMarker::~TimelineMarker()
{
}

QRectF TimelineMarker::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
		20 + penWidth, 20 + penWidth);
}

void TimelineMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	//option->styleObject();
	painter->drawLine(0, 5, 0, 400);

	QPainterPath painterPath;
	painterPath.moveTo(-4, -5);
	painterPath.lineTo(4, -5);
	painterPath.lineTo(4, 0);
	painterPath.lineTo(0, 4);
	painterPath.lineTo(-4, 0);
	painterPath.lineTo(-4, -5);

	//scene.addPath(painterPath, QPen(QColor(0, 0, 0), 1, Qt::SolidLine), QColor(50, 200, 10));
	painter->drawPath(painterPath);
}