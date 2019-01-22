#include "trackaudiolevel.h"

#include <QPainter>

TrackAudioLevel::TrackAudioLevel(QWidget *parent)
	: QWidget(parent)
	, m_level(0.0)
{
    setMinimumHeight(8);
	setMaximumHeight(30);
}

TrackAudioLevel::~TrackAudioLevel()
{
}

void TrackAudioLevel::setLevel(qreal level)
{
    if (m_level != level) {
		m_level = level;
		update();
	}
}

void TrackAudioLevel::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	// draw level
	qreal widthLevel = m_level * width();
	painter.fillRect(0, 0, widthLevel, height(), Qt::red);
	// clear the rest of the control
	painter.fillRect(widthLevel, 0, width(), height(), Qt::black);
}
