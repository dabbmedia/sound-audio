#include "qaudiolevel.h"

#include <QPainter>

QAudioLevel::QAudioLevel(QWidget *parent)
	: QWidget(parent)
	, m_level(0.0)
{
	setMinimumHeight(15);
	setMaximumHeight(30);
}

QAudioLevel::~QAudioLevel()
{
}

void QAudioLevel::setLevel(qreal level)
{
	if (m_level != level) {
		m_level = level;
		update();
	}
}

void QAudioLevel::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	// draw level
	qreal widthLevel = m_level * width();
	painter.fillRect(0, 0, widthLevel, height(), Qt::red);
	// clear the rest of the control
	painter.fillRect(widthLevel, 0, width(), height(), Qt::black);
}
