#include "project.h"
#include "track.h"

#include <QLinkedList>

Project::Project(QObject *parent)
	: QObject(parent)
{
	Track *defaultTrack = new Track(this);
	trackList.append(defaultTrack);
}

Project::~Project()
{
}
