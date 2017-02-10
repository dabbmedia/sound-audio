#include "track.h"

#include <QAudioProbe>
#include <QGraphicsItem>
#include <QMultimedia>
#include <QtDebug>
#include <QUrl>

static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

Track::Track(QObject *parent) : QObject(parent)
{
	
}

Track::~Track()
{
	delete audioRecorder;
	delete probe;
}

QStringList Track::getAudioDevices() {
	audioRecorder = new QAudioRecorder(this);
	probe = new QAudioProbe;
	connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
	probe->setSource(audioRecorder);

	return audioRecorder->audioInputs();
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
		//clearAudioLevels();
		statusMessage = tr("Paused");
		break;
	case QMediaRecorder::UnloadedStatus:
	case QMediaRecorder::LoadedStatus:
		//clearAudioLevels();
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
	if (audioRecorder->state() == QMediaRecorder::StoppedState) {
		audioRecorder->setAudioInput(sAudioInput);

		QAudioEncoderSettings settings;
		settings.setCodec(sCodec);
		settings.setSampleRate(intSampleRate);
		settings.setBitRate(intBitRate);
		settings.setChannelCount(intChannelCount);
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

void Track::setOutputLocation()
{
	/*QString fileName = QFileDialog::getSaveFileName();
	audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));*/

	QString fileName = "default-track.wav"; //change to auto-increment name and save in project audio folder
	audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
	outputLocationSet = true;
}

void Track::displayErrorMessage()
{
	qDebug() << audioRecorder->errorString();
}

void Track::clearAudioLevels()
{
	/*for (int i = 0; i < audioLevels.size(); ++i)
		audioLevels.at(i)->setLevel(0);*/
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
			QAudioLevel *level = new QAudioLevel(ui->centralwidget);
			audioLevels.append(level);
			ui->levelsLayout->addWidget(level);
		}
	}

	QVector<qreal> levels = getBufferLevels(buffer);
	for (int i = 0; i < levels.count(); ++i)
		audioLevels.at(i)->setLevel(levels.at(i));*/
}
