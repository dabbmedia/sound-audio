#pragma once

#ifndef QAUDIOLEVEL_H
#define QAUDIOLEVEL_H

#include <QWidget>

class TrackAudioLevel : public QWidget
{
	Q_OBJECT

public:
    explicit TrackAudioLevel(QWidget *parent = 0);
    ~TrackAudioLevel();

	// Using [0; 1.0] range
	void setLevel(qreal level);

protected:
	void paintEvent(QPaintEvent *event);

private:
	qreal m_level;
};

#endif // QAUDIOLEVEL_H
