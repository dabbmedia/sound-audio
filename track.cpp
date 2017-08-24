#include "track.h"
#include "qaudiolevel.h"

#include <QAudio>
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
#include <QPushButton>
#include <QUrl>
#include <QVideoEncoderSettings>
#include <QWidget>
#include <QtDebug>

static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

Track::Track(trackTypes trackType, QString projectAudioPath, QObject *parent) : QObject(parent)
{
	name = "test track";
	audioRecorder = new QAudioRecorder(this);
	probe = new QAudioProbe;
	connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
	probe->setSource(audioRecorder);

	foreach(const QString &codecName, audioRecorder->supportedAudioCodecs()) {
		if (codecName.contains("wav", Qt::CaseInsensitive)) {
			sCodec = codecName;
		}
	}

	foreach(int sampleRate, audioRecorder->supportedAudioSampleRates()) {
		intSampleRate = sampleRate;
	}

	intBitRate = 96000;
	intChannelCount = 1;
	setOutputLocation(projectAudioPath);
}

Track::~Track()
{
	delete audioRecorder;
	delete probe;
}

QStringList Track::getAudioDevices() {
	return audioRecorder->audioInputs();
}

QWidget * Track::getTrackControlsTimelineWidget() {
	trackControls = new QWidget;
	trackControls->setFixedHeight(48);
	trackControls->setMinimumSize(QSize(120, 48));
	trackControls->setContentsMargins(2, 2, 2, 2);

	QLineEdit *lineEditTrackName = new QLineEdit;
	lineEditTrackName->setText("Track Name");

	btnArm = new QPushButton("R", trackControls);
	btnArm->setFixedSize(16, 16);
	btnArm->setFont(QFont("Helvetica", 6));
	btnArm->setCheckable(true);
	//connect(btnArm, SIGNAL(clicked()), this, SLOT(toggleRecord()));

	btnMute = new QPushButton("M", trackControls);
	btnMute->setFixedSize(16, 16);
	btnMute->setFont(QFont("Helvetica", 6));

	btnSolo = new QPushButton("S", trackControls);
	btnSolo->setFixedSize(16, 16);
	btnSolo->setFont(QFont("Helvetica", 6));

	QComboBox *trackInputDevice = new QComboBox;
	trackInputDevice->setFont(QFont("Helvetica", 6));
	trackInputDevice->setToolTip("Input Device");

	QStringList devices = getAudioDevices();
	for (int i = 0; i < devices.size(); i++)
	{
		trackInputDevice->insertItem(i, devices.at(i));
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

	level = new QAudioLevel(trackControls);
	audioLevels.append(level);
	trackControls->layout()->addWidget(level);

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

void Track::toggleRecord()
{
	qDebug() << "toggleREcord called";
	if (audioRecorder->state() == QMediaRecorder::StoppedState) {
		sAudioInput = audioRecorder->defaultAudioInput();
		audioRecorder->setAudioInput(sAudioInput);

		settings;
		
		settings.setCodec(sCodec);
		settings.setSampleRate(intSampleRate);
		settings.setBitRate(intBitRate);
		settings.setChannelCount(intChannelCount); //output channel count?
		settings.setQuality(QMultimedia::EncodingQuality(QMultimedia::NormalQuality));
		settings.setEncodingMode(QMultimedia::ConstantQualityEncoding); //QMultimedia::ConstantBitRateEncoding

		QString container = audioRecorder->supportedContainers()[0];

		audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
		audioRecorder->record();
	}
	else {
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
	//QFile sourceFile;
	switch (newState) {
	case QAudio::IdleState:
		// Finished playing (no more data)
		audioOutput->stop();
		//sourceFile.setFileName(audioFiles.at(audioFileIndex).file);
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
	QDir audioPath(projectAudioPath);
	if (!audioPath.exists()) {
		audioPath.mkdir(projectAudioPath);
	}

	QString fileExtension = ".wav";
	QString fileName = projectAudioPath + "/" + name.replace(" ", "-") + "-" + QString::number(QDateTime::currentMSecsSinceEpoch()) + fileExtension;
	
	AudioFile audioFile;
	audioFile.startPos = 0;
	audioFile.file = fileName;
	audioFiles << audioFile;
	
	audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
	outputLocationSet = true;
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
	/*if (audioLevels.count() != buffer.format().channelCount()) {
		qDeleteAll(audioLevels);
		audioLevels.clear();
		for (int i = 0; i < buffer.format().channelCount(); ++i) {
			level = new QAudioLevel(trackControls);
			audioLevels.append(level);
			trackControls->layout()->addWidget(level);
		}
	}*/

	QVector<qreal> levels = getBufferLevels(buffer);
	for (int i = 0; i < levels.count(); ++i)
		audioLevels.at(i)->setLevel(levels.at(i));
}
