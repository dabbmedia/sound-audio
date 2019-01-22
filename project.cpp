#include "project.h"
#include "track.h"

#include <QList>
#include <QMessageBox>
#include <QXmlStreamReader>

Project::Project(QObject *parent)
	: QObject(parent)
{
	/*Track *defaultTrack = new Track(this);
	trackList.append(defaultTrack);*/
}

Project::Project(QString fileName)
{
    if (fileName.isEmpty())
		return;

	QFile fileFile(fileName);
	if (!fileFile.open(QFile::ReadOnly | QFile::Text)) {
		emit signalProjectError(tr("Cannot read project file %1:\n%2.").arg(fileName).arg(fileFile.errorString()));
		qDebug() << "Cannot read file " << fileName << ":" << fileFile.errorString();
		return;
    }

	xmlRead.setDevice(&fileFile);

	if (xmlRead.readNextStartElement()) {
		if (xmlRead.name() == "project")
			readXML();
		else
			xmlRead.raiseError(QObject::tr("The file is not a SoundAudio version 0.1 project file."));
    }
}

Project::~Project()
{
}

void Project::addTrack() {
    Track *track = new Track(audio, path + "/audio", this);
	
	if (track) {
        tracks << track;
		writeProjectSettings();
	}
	else {
        qDebug() << "Project::addTrack: error creating track";
	}
}

void Project::readXML()
{
	Q_ASSERT(xmlRead.isStartElement() && xmlRead.name() == "project");

	while (xmlRead.readNextStartElement()) {
		if (xmlRead.name() == "name")
			readName();
		else if (xmlRead.name() == "path")
			readPath();
		else if (xmlRead.name() == "file")
			readFile();
		/*else if (xmlRead.name() == "tracks")
			readTracks();*/
		else
			xmlRead.skipCurrentElement();
	}
}

void Project::readName()
{
	Q_ASSERT(xmlRead.isStartElement() && xmlRead.name() == "name");

	name = xmlRead.readElementText();
}

void Project::readPath()
{
	Q_ASSERT(xmlRead.isStartElement() && xmlRead.name() == "path");

	path = xmlRead.readElementText();
}

void Project::readFile()
{
	Q_ASSERT(xmlRead.isStartElement() && xmlRead.name() == "file");

	file = xmlRead.readElementText();
}

void Project::readTracks()
{
	Q_ASSERT(xmlRead.isStartElement() && xmlRead.name() == "tracks");

	//tracks = xmlRead.readElementText();
}

void Project::writeProjectSettings()
{
	QString fileName = file;
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		qDebug() << "could not open file " << fileName;
	}

	xmlWrite.setDevice(&file);
	xmlWrite.setAutoFormatting(true);
	xmlWrite.writeStartDocument();

	xmlWrite.writeStartElement("project");

	if (name.isEmpty() == false && path.isEmpty() == false) {
		xmlWrite.writeStartElement("name");
		xmlWrite.writeCharacters(name);
		xmlWrite.writeEndElement(); //name

		xmlWrite.writeStartElement("path");
		xmlWrite.writeCharacters(path);
		xmlWrite.writeEndElement(); //path

		xmlWrite.writeStartElement("tracks");
		xmlWrite.writeCharacters(path);
		for (int i = 0; i < tracks.size(); ++i) {
            Track *track = tracks.at(i);

			xmlWrite.writeStartElement("track");
			xmlWrite.writeCharacters(track->name);
			xmlWrite.writeEndElement(); //path
		}
		xmlWrite.writeEndElement(); //tracks
	}

	xmlWrite.writeEndDocument();
}

