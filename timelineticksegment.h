#pragma once

#include <QGraphicsWidget>

class TimelineTickSegment :
	public QGraphicsWidget
{
public:
	TimelineTickSegment();
	~TimelineTickSegment();
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	float flFramesPerSecond;
	int intWidth;
};

