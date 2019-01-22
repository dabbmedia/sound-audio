#ifndef TRACK_H
#define TRACK_H

#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QIODevice>
#include <QList>
#include <QMediaRecorder>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class TrackAudioLevel;
class Project;
//#include "project.h"
#include "trackaudiolevel.h"

enum trackTypes { audio, midi, video };
struct AudioFile {
	int startPos;
	QString file;
};

class TrackAudioInfo : public QIODevice
{
    Q_OBJECT

public:
    TrackAudioInfo(const QAudioFormat &format);

    void start();
    void stop();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

    const QAudioFormat m_format;
    quint32 m_maxAmplitude = 0;
    qreal m_level = 0.0; // 0.0 <= m_level <= 1.0

signals:
    void update();
};

class Track : public QObject
{
	Q_OBJECT

public:
    Track(trackTypes trackType, QString projectAudioPath, QObject *parent = 0);
	~Track();
    QStringList* getAudioDevices();
	void clearAudioLevels();
	void setOutputLocation(QString projectAudioPath);
	QWidget * getTrackControlsTimelineWidget();
	QAudioRecorder *audioRecorder;
	QAudioProbe *probe;
	QAudioEncoderSettings settings;
    QAudioFormat format;
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
//	QAudioLevel *level;
    TrackAudioLevel *widgetAudioLevel;
    QSlider *sliderTrackVolume;
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
    void stop();
    void armTrack();
	void handleStateChanged(QAudio::State newState);
    void setAudioLevel(qreal level);

private slots:
	void updateStatus(QMediaRecorder::Status);
	void onStateChanged(QMediaRecorder::State);
	void updateProgress(qint64 pos);
    void displayErrorMessage();

private:
    QList<TrackAudioLevel*> audioLevels;
	bool outputLocationSet;
    QScopedPointer<TrackAudioInfo> m_audioInfo;
    QScopedPointer<QAudioInput> m_audioInput;
    bool m_pullMode = true;

};

#endif // TRACK_H
