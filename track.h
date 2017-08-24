#ifndef TRACK_H
#define TRACK_H

#include <QAudioOutput>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QList>
#include <QMediaRecorder>
#include <QObject>
#include <QPushButton>
#include <QWidget>

class QAudioRecorder;
class QAudioProbe;
class QAudioBuffer;
class QAudioLevel;
class Project;

enum trackTypes { audio, midi, video };
struct AudioFile {
	int startPos;
	QString file;
};

class Track : public QObject
{
	Q_OBJECT

public:
	Track(trackTypes trackType, QString projectAudioPath, QObject *parent = 0);
	~Track();
	QStringList getAudioDevices();
	void clearAudioLevels();
	void setOutputLocation(QString projectAudioPath);
	QWidget * getTrackControlsTimelineWidget();
	QAudioRecorder *audioRecorder;
	QAudioProbe *probe;
	QAudioEncoderSettings settings;
	QString name;
	QString sAudioInput;
	QString sCodec; //remove and read from project object
	QString sQuality; //remove and read from project object
	QString sEncodingMode; //remove and read from project object
	QHBoxLayout *hboxTrackName;
	QVBoxLayout *vboxTrackName;
	QWidget *trackControls;
	QPushButton *btnArm;
	QPushButton *btnMute;
	QPushButton *btnSolo;
	QAudioLevel *level;
	QAudioOutput *audioOutput;
	QList<AudioFile> audioFiles;
	QFile sourceFile;
	int intSampleRate;
	int intBitRate;
	int intChannelCount;
	int audioFileIndex;

public slots:
	void processBuffer(const QAudioBuffer&);
	void togglePause();
	void toggleRecord();
	void togglePlay();
	void handleStateChanged(QAudio::State newState);

private slots:
	void updateStatus(QMediaRecorder::Status);
	void onStateChanged(QMediaRecorder::State);
	void updateProgress(qint64 pos);
	void displayErrorMessage();

private:
	QList<QAudioLevel*> audioLevels;
	bool outputLocationSet;

};

#endif // TRACK_H
