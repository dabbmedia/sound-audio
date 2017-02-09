#pragma once

#include <QGraphicsItem>

class TimelineMarker :
	public QGraphicsItem
{
public:
	TimelineMarker();
	~TimelineMarker();
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

