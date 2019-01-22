#include "project.h"
#include "trackaudiolevel.h"
#include "track.h"

#include <QAudio>
#include <QAudioDeviceInfo>
#include <QAudioEncoderSettings>
#include <QAudioOutput>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QComboBox>
#include <QDateTime>
#include <QDir>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMultimedia>
#include <QObject>
#include <QPainter>
#include <QPushButton>
#include <QSlider>
#include <QUrl>
#include <QVideoEncoderSettings>
#include <QWidget>
#include <QtDebug>
#include <qendian.h>

static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

TrackAudioInfo::TrackAudioInfo(const QAudioFormat &format)
    : m_format(format)
{
    switch (m_format.sampleSize()) {
    case 8:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 255;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 127;
            break;
        default:
            break;
        }
        break;
    case 16:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 65535;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 32767;
            break;
        default:
            break;
        }
        break;

    case 32:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 0xffffffff;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 0x7fffffff;
            break;
        case QAudioFormat::Float:
            m_maxAmplitude = 0x7fffffff; // Kind of
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void TrackAudioInfo::start()
{
    open(QIODevice::WriteOnly);
}

void TrackAudioInfo::stop()
{
    close();
}

qint64 TrackAudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 TrackAudioInfo::writeData(const char *data, qint64 len)
{
    if (m_maxAmplitude) {
        Q_ASSERT(m_format.sampleSize() % 8 == 0);
        const int channelBytes = m_format.sampleSize() / 8;
        const int sampleBytes = m_format.channelCount() * channelBytes;
        Q_ASSERT(len % sampleBytes == 0);
        const int numSamples = len / sampleBytes;

        quint32 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < m_format.channelCount(); ++j) {
                quint32 value = 0;

                if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    value = *reinterpret_cast<const quint8*>(ptr);
                } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    value = qAbs(*reinterpret_cast<const qint8*>(ptr));
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint16>(ptr);
                    else
                        value = qFromBigEndian<quint16>(ptr);
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint16>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint16>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint32>(ptr);
                    else
                        value = qFromBigEndian<quint32>(ptr);
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint32>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint32>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::Float) {
                    value = qAbs(*reinterpret_cast<const float*>(ptr) * 0x7fffffff); // assumes 0-1.0
                }

                maxValue = qMax(value, maxValue);
                ptr += channelBytes;
            }
        }

        maxValue = qMin(maxValue, m_maxAmplitude);
        m_level = qreal(maxValue) / m_maxAmplitude;
    }

    emit update();
    return len;
}

Track::Track(trackTypes trackType, QString projectAudioPath, QObject *parent) : QObject(parent)
{
	name = "test track";
//	foreach(const QString &codecName, audioRecorder->supportedAudioCodecs()) {
//		if (codecName.contains("wav", Qt::CaseInsensitive)) {
//			sCodec = codecName;
//		}
//	}

//	foreach(int sampleRate, audioRecorder->supportedAudioSampleRates()) {
//		intSampleRate = sampleRate;
//	}

	intBitRate = 96000;
	intChannelCount = 1;
//	setOutputLocation(projectAudioPath);

    format.setSampleRate(8000);//intSampleRate
    format.setChannelCount(1);//intChannelCount
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");//sCodec
}

Track::~Track()
{
	delete audioRecorder;
	delete probe;
}

QStringList* Track::getAudioDevices() {
    QList<QAudioDeviceInfo> audioDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QStringList *audioDevicesNames = new QStringList;
    for (int i = 0; i < audioDevices.size(); i++) {
        audioDevicesNames->append(audioDevices.at(i).deviceName());
    }
    return audioDevicesNames;
}

QWidget * Track::getTrackControlsTimelineWidget() {
	trackControls = new QWidget;
//	trackControls->setFixedHeight(48);
    trackControls->setMinimumSize(QSize(120, 56));
	trackControls->setContentsMargins(2, 2, 2, 2);

	QLineEdit *lineEditTrackName = new QLineEdit;
	lineEditTrackName->setText("Track Name");

	btnArm = new QPushButton("R", trackControls);
	btnArm->setFixedSize(16, 16);
	btnArm->setFont(QFont("Helvetica", 6));
	btnArm->setCheckable(true);
    connect(btnArm, SIGNAL(clicked()), this, SLOT(armTrack()));

	btnMute = new QPushButton("M", trackControls);
	btnMute->setFixedSize(16, 16);
	btnMute->setFont(QFont("Helvetica", 6));

	btnSolo = new QPushButton("S", trackControls);
	btnSolo->setFixedSize(16, 16);
	btnSolo->setFont(QFont("Helvetica", 6));

	QComboBox *trackInputDevice = new QComboBox;
	trackInputDevice->setFont(QFont("Helvetica", 6));
	trackInputDevice->setToolTip("Input Device");

    QStringList *devices = getAudioDevices();
    for (int i = 0; i < devices->size(); i++)
    {
        trackInputDevice->insertItem(i, devices->at(i));
    }

	hboxTrackName = new QHBoxLayout;
	hboxTrackName->setContentsMargins(0, 0, 0, 0);
	hboxTrackName->setAlignment(Qt::AlignTop);
	hboxTrackName->addWidget(lineEditTrackName);
	hboxTrackName->addWidget(btnArm);
	hboxTrackName->addWidget(btnMute);
	hboxTrackName->addWidget(btnSolo);
	hboxTrackName->addWidget(trackInputDevice);

	/*QHBoxLayout *hboxTrackInput = new QHBoxLayout;
	hboxTrackInput->setContentsMargins(0, 0, 0, 0);
	hboxTrackInput->setAlignment(Qt::AlignTop);
	hboxTrackInput->addWidget(trackInputDevice);*/

	vboxTrackName = new QVBoxLayout;
	vboxTrackName->setContentsMargins(0, 0, 0, 0);
	vboxTrackName->setAlignment(Qt::AlignTop);
	//vboxTrackName->SetMinimumSize(QSize(120, 48));
	vboxTrackName->addLayout(hboxTrackName);
	//vboxTrackName->addLayout(hboxTrackInput);

	trackControls->setLayout(vboxTrackName);

    widgetAudioLevel = new TrackAudioLevel(trackControls);
    trackControls->layout()->addWidget(widgetAudioLevel);

    sliderTrackVolume = new QSlider;
    sliderTrackVolume->setTickInterval(1);
    sliderTrackVolume->setValue(50);
    sliderTrackVolume->setMinimumSize(120, 8);
    sliderTrackVolume->setOrientation(Qt::Orientation::Horizontal);
    trackControls->layout()->addWidget(sliderTrackVolume);

	return trackControls;
}

void Track::updateProgress(qint64 duration)
{
	if (audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
		return;

	//signal timelineMarker position here
	//ui->statusbar->showMessage(tr("Recorded %1 sec").arg(duration / 1000));
}

void Track::updateStatus(QMediaRecorder::Status status)
{
	QString statusMessage;

	switch (status) {
	case QMediaRecorder::RecordingStatus:
		statusMessage = tr("Recording to %1").arg(audioRecorder->actualLocation().toString());
		break;
	case QMediaRecorder::PausedStatus:
		clearAudioLevels();
		statusMessage = tr("Paused");
		break;
	case QMediaRecorder::UnloadedStatus:
	case QMediaRecorder::LoadedStatus:
		clearAudioLevels();
		statusMessage = tr("Stopped");
    default:
		break;
	}

	/*if (audioRecorder->error() == QMediaRecorder::NoError)
		ui->statusbar->showMessage(statusMessage);*/
}

void Track::onStateChanged(QMediaRecorder::State state)
{
	/*switch (state) {
	case QMediaRecorder::RecordingState:
		ui->recordButton->setText(tr("Stop"));
		ui->pauseButton->setText(tr("Pause"));
		break;
	case QMediaRecorder::PausedState:
		ui->recordButton->setText(tr("Stop"));
		ui->pauseButton->setText(tr("Resume"));
		break;
	case QMediaRecorder::StoppedState:
		ui->recordButton->setText(tr("Record"));
		ui->pauseButton->setText(tr("Pause"));
		break;
	}

	ui->pauseButton->setEnabled(audioRecorder->state() != QMediaRecorder::StoppedState);*/
}

void Track::armTrack() {
    if (btnArm->isChecked()) {
        QAudioDeviceInfo deviceInfo = QAudioDeviceInfo::defaultInputDevice();

        if (!deviceInfo.isFormatSupported(format)) {
            qWarning() << "Default format not supported - trying to use nearest";
            format = deviceInfo.nearestFormat(format);
        }

        m_audioInfo.reset(new TrackAudioInfo(format));
        connect(m_audioInfo.data(), &TrackAudioInfo::update, [this]() {
            setAudioLevel(m_audioInfo->level());
        });

        m_audioInput.reset(new QAudioInput(deviceInfo, format));
        qreal initialVolume = QAudio::convertVolume(m_audioInput->volume(),
                                                    QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);
    //    m_volumeSlider->setValue(qRound(initialVolume * 100));
        sliderTrackVolume->setValue(qRound(initialVolume * 100));
        m_audioInfo->start();
        m_audioInput->stop();

        m_audioInput->start(m_audioInfo.data());
    } else {
        m_audioInput->suspend();
    }
}

void Track::setAudioLevel(qreal level) {
    qDebug() << level;
    widgetAudioLevel->setLevel(level);
}

void Track::toggleRecord()
{
	qDebug() << "toggleREcord called";
    if (audioRecorder && audioRecorder->state() != QMediaRecorder::RecordingState) {
//		sAudioInput = audioRecorder->defaultAudioInput();
//        audioRecorder->setAudioInput(sAudioInput);
		audioRecorder->record();
	}
	else {
		audioRecorder->stop();
	}
}

void Track::stop()
{
    qDebug() << "Track::stop called";
    if (audioRecorder->state() == QMediaRecorder::PausedState || audioRecorder->state() == QMediaRecorder::RecordingState) {
        audioRecorder->stop();
    }
}

void Track::togglePause()
{
	if (audioRecorder->state() != QMediaRecorder::PausedState)
		audioRecorder->pause();
	else
		audioRecorder->record();
}

void Track::togglePlay() {
	audioOutput = new QAudioOutput;

	QAudioFormat format;
	// Set up the format, eg.
	format.setSampleRate(intSampleRate);
	format.setChannelCount(intChannelCount);
	format.setSampleSize(8);
	format.setCodec("audio/pcm"); //sCodec
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::UnSignedInt);

	for (audioFileIndex = 0; audioFileIndex < audioFiles.size(); ++audioFileIndex) {
		if (!audioFiles.at(audioFileIndex).file.isEmpty()) {
			sourceFile.setFileName(audioFiles.at(audioFileIndex).file);
			sourceFile.open(QIODevice::ReadOnly);

			audioOutput = new QAudioOutput(format, this);
			connect(audioOutput, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
			audioOutput->start(&sourceFile);
		}
		else {
			qDebug() << "could not play audio file, file name empty";
		}
	}
}

void Track::handleStateChanged(QAudio::State newState)
{
    qDebug() << "handleStateChanged...";
	//QFile sourceFile;
	switch (newState) {
	case QAudio::IdleState:
		// Finished playing (no more data)
		audioOutput->stop();
        sourceFile.setFileName(audioFiles.at(audioFileIndex).file);
		sourceFile.close();
		delete audioOutput;
		break;

	case QAudio::StoppedState:
		// Stopped for other reasons
		if (audioOutput->error() != QAudio::NoError) {
			// Error handling
			qDebug() << "error stopping audio playback";
		}
		break;

	default:
		// ... other cases as appropriate
		break;
	}
}

void Track::setOutputLocation(QString projectAudioPath)
{
//	QDir audioPath(projectAudioPath);
//	if (!audioPath.exists()) {
//		audioPath.mkdir(projectAudioPath);
//	}

//	QString fileExtension = ".wav";
//	QString fileName = projectAudioPath + "/" + name.replace(" ", "-") + "-" + QString::number(QDateTime::currentMSecsSinceEpoch()) + fileExtension;
	
//	AudioFile audioFile;
//	audioFile.startPos = 0;
//	audioFile.file = fileName;
//	audioFiles << audioFile;
	
//	audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
//	outputLocationSet = true;
}

void Track::displayErrorMessage()
{
	qDebug() << audioRecorder->errorString();
}

void Track::clearAudioLevels()
{
	for (int i = 0; i < audioLevels.size(); ++i)
		audioLevels.at(i)->setLevel(0);
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
	// Note: Only the most common sample formats are supported
	if (!format.isValid())
		return qreal(0);

	if (format.codec() != "audio/pcm")
		return qreal(0);

	switch (format.sampleType()) {
	case QAudioFormat::Unknown:
		break;
	case QAudioFormat::Float:
		if (format.sampleSize() != 32) // other sample formats are not supported
			return qreal(0);
		return qreal(1.00003);
	case QAudioFormat::SignedInt:
		if (format.sampleSize() == 32)
			return qreal(INT_MAX);
		if (format.sampleSize() == 16)
			return qreal(SHRT_MAX);
		if (format.sampleSize() == 8)
			return qreal(CHAR_MAX);
		break;
	case QAudioFormat::UnSignedInt:
		if (format.sampleSize() == 32)
			return qreal(UINT_MAX);
		if (format.sampleSize() == 16)
			return qreal(USHRT_MAX);
		if (format.sampleSize() == 8)
			return qreal(UCHAR_MAX);
		break;
	}

	return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
	QVector<qreal> values;

	if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
		return values;

	if (buffer.format().codec() != "audio/pcm")
		return values;

	int channelCount = buffer.format().channelCount();
	values.fill(0, channelCount);
	qreal peak_value = getPeakValue(buffer.format());
	if (qFuzzyCompare(peak_value, qreal(0)))
		return values;

	switch (buffer.format().sampleType()) {
	case QAudioFormat::Unknown:
	case QAudioFormat::UnSignedInt:
		if (buffer.format().sampleSize() == 32)
			values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 16)
			values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 8)
			values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
		for (int i = 0; i < values.size(); ++i)
			values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
		break;
	case QAudioFormat::Float:
		if (buffer.format().sampleSize() == 32) {
			values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
			for (int i = 0; i < values.size(); ++i)
				values[i] /= peak_value;
		}
		break;
	case QAudioFormat::SignedInt:
		if (buffer.format().sampleSize() == 32)
			values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 16)
			values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 8)
			values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
		for (int i = 0; i < values.size(); ++i)
			values[i] /= peak_value;
		break;
	}

	return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
	QVector<qreal> max_values;
	max_values.fill(0, channels);

	for (int i = 0; i < frames; ++i) {
		for (int j = 0; j < channels; ++j) {
			qreal value = qAbs(qreal(buffer[i * channels + j]));
			if (value > max_values.at(j))
				max_values.replace(j, value);
		}
	}

	return max_values;
}

void Track::processBuffer(const QAudioBuffer& buffer)
{
//    qDebug() << "Track::processBuffer audioLevels.count(): " << audioLevels.count() << ", channelCount: " << buffer.format().channelCount();
//    if (audioLevels.count() != buffer.format().channelCount()) {
//		qDeleteAll(audioLevels);
//		audioLevels.clear();
//		for (int i = 0; i < buffer.format().channelCount(); ++i) {
//			level = new QAudioLevel(trackControls);
//            qDebug() << "Track::processBuffer level: " << level;
//            audioLevels.append(level);
//			trackControls->layout()->addWidget(level);
//		}
//    }

//	QVector<qreal> levels = getBufferLevels(buffer);
//	for (int i = 0; i < levels.count(); ++i)
//		audioLevels.at(i)->setLevel(levels.at(i));
}
