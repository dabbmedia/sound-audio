#pragma once

#include "track.h"

#include <QLinkedList>
#include <QObject>

class Project : public QObject
{
	Q_OBJECT

public:
	Project(QObject *parent);
	~Project();
	int intCurrentPosition;
	QLinkedList<Track *> trackList;
};
