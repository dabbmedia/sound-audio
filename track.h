#pragma once

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QGraphicsItem>
#include <QObject>

class QAudioRecorder;
class QAudioProbe;
class QAudioBuffer;

class QAudioLevel;

class Track : public QObject
{
	Q_OBJECT

public:
	Track(QObject *parent);
	~Track();
	QStringList getAudioDevices();
	void clearAudioLevels();
	QAudioRecorder *audioRecorder;
	QAudioProbe *probe;
	QString sAudioInput;
	QString sCodec;
	int intSampleRate;
	int intBitRate;
	int intChannelCount;
	QString sQuality;
	QString sEncodingMode;

public slots:
	void processBuffer(const QAudioBuffer&);

private slots:
	void setOutputLocation();
	void togglePause();
	void toggleRecord();

	void updateStatus(QMediaRecorder::Status);
	void onStateChanged(QMediaRecorder::State);
	void updateProgress(qint64 pos);
	void displayErrorMessage();

private:
	QList<QAudioLevel*> audioLevels;
	bool outputLocationSet;

};
