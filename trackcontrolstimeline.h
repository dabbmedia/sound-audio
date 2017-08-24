#pragma once

#include <QGraphicsWidget>

class TrackControlsTimeline : public QGraphicsWidget
{
	Q_OBJECT

public:
	TrackControlsTimeline();
	~TrackControlsTimeline();
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	int intWidth;
};
