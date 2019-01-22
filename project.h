#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "track.h"

class Project : public QObject
{
	Q_OBJECT

public:
	Project(QObject *parent = 0);
	Project(QString fileName);
	~Project();
	void writeProjectSettings();
	int intCurrentPosition;
	QList<Track *> tracks;
	QString name;
	QString file;
	QString path;
	QString sCodec;
	QString sQuality;
	QString sEncodingMode;
	QXmlStreamReader xmlRead;
	QXmlStreamWriter xmlWrite;

protected:
	void readXML();
	void readName();
	void readPath();
	void readFile();
	void readTracks();

public slots:
    void addTrack();

signals:
	void signalTrackAdded(int newTrackIndex);
	void signalProjectError(QString errorMessage);
};

#endif // PROJECT_H
