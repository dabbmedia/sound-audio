#include "project.h"
#include "timelineeditor.h"
#include "timeline.h"
#include "track.h"

#include <QApplication>
#include <QBrush>
#include <QComboBox>
#include <QGraphicsRectItem>
#include <QLineEdit>
#include <QLinkedList>
#include <QMainWindow>
#include <QPen>
#include <QPushButton>
#include <QRectF>
#include <QRegularExpression>
#include <QScrollBar>
#include <QSettings>
#include <QSplitter>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtDebug>

TimelineEditor::TimelineEditor(QWidget *parent) : QWidget(parent)
{
	vboxTimelineEditorContainer = new QVBoxLayout();
    vboxTimelineEditorContainer->setSpacing(0);
    vboxTimelineEditorContainer->setContentsMargins(0, 0, 0, 0);

	currentTimeline = new Timeline(this);

	createToolBar();

	createTracksLayout();

    setLayout(vboxTimelineEditorContainer);
}

void TimelineEditor::createToolBar() {
	QToolButton *btnClipSelect = new QToolButton(this);
	btnClipSelect->setFixedSize(QSize(32, 32));
	btnClipSelect->setIcon(QIcon(":/icon-arrow-select.svg"));
	btnClipSelect->setToolTip("Select");
	//    connect(btnClipSelect, SIGNAL (clicked()), this, SLOT (stopMainTimer()));

	QToolButton *btnClipSplit = new QToolButton(this);
	btnClipSplit->setFixedSize(QSize(32, 32));
	QPixmap pmSplit(":/icon-split.svg");
	QIcon iconSplit(pmSplit);
	btnClipSplit->setIcon(iconSplit);
	btnClipSplit->setToolTip("Split");
	//    connect(btnClipSplit, SIGNAL (clicked()), this, SLOT (stopMainTimer()));

	btnAddTrack = new QToolButton(this);
	btnAddTrack->setFixedSize(QSize(32, 32));
	btnAddTrack->setIcon(QIcon(":/icon-add.svg"));
	btnAddTrack->setToolTip("Add Track");

	QToolButton *btnZoomOut = new QToolButton(this);
    btnZoomOut->setText("Zoom Out -");
	btnZoomOut->setFixedSize(QSize(32, 32));
	btnZoomOut->setStyleSheet("QToolButton { text-align: right; }");
	btnZoomOut->setToolTip("Zoom In");
    btnZoomOut->setShortcut(Qt::CTRL + Qt::Key_Minus);
    QPixmap pmZoomOut(":/icon-zoom-out.svg");
    QIcon iconZoomOut(pmZoomOut);
    btnZoomOut->setIcon(iconZoomOut);
    connect(btnZoomOut, SIGNAL(clicked()), currentTimeline, SLOT(zoomOut()));

	QToolButton *btnZoomIn = new QToolButton(this);
    btnZoomIn->setText("Zoom In +");
	btnZoomIn->setFixedSize(QSize(32, 32));
	btnZoomIn->setStyleSheet("QToolButton { right: 0; }");
	btnZoomIn->setToolTip("Zoom Out");
	btnZoomIn->setShortcut(Qt::CTRL + Qt::Key_Plus);
    QPixmap pmZoomIn(":/icon-zoom-in.svg");
    QIcon iconZoomIn(pmZoomIn);
    btnZoomIn->setIcon(iconZoomIn);
    connect(btnZoomIn, SIGNAL(clicked()), currentTimeline, SLOT(zoomIn()));

	QToolBar *toolBarTimelineEditor = new QToolBar;
	toolBarTimelineEditor->setIconSize(QSize(12, 12));
	toolBarTimelineEditor->addWidget(btnClipSelect);
	toolBarTimelineEditor->addWidget(btnClipSplit);
	toolBarTimelineEditor->addWidget(btnAddTrack);
	toolBarTimelineEditor->addSeparator();
	toolBarTimelineEditor->addWidget(btnZoomOut);
	toolBarTimelineEditor->addWidget(btnZoomIn);

	vboxTimelineEditorContainer->addWidget(toolBarTimelineEditor);
}

void TimelineEditor::createTracksLayout() {
	vboxTrackNameFrame = new QVBoxLayout();
	vboxTrackNameFrame->setSpacing(0);
	vboxTrackNameFrame->setContentsMargins(0, 0, 0, 0);
	vboxTrackNameFrame->setAlignment(Qt::AlignTop);

	//add track name header
	QWidget *trackNameHeader = new QWidget;
	trackNameHeader->setContentsMargins(0, 0, 0, 0);
	trackNameHeader->setStyleSheet("QWidget { border: 0; background-color: #333333; }");
	trackNameHeader->setFixedHeight(24);
	vboxTrackNameFrame->addWidget(trackNameHeader);
	
	vboxTimelineFrame = new QVBoxLayout();
	vboxTimelineFrame->setSpacing(0);
	vboxTimelineFrame->setContentsMargins(0, 0, 0, 0);
	vboxTimelineFrame->setAlignment(Qt::AlignTop);

	//connect(currentTimeline, SIGNAL(signalDisplay(int)), this, SLOT(setCurrentPosition(int)));
	//connect(currentTimeline, SIGNAL(signalTrackAdded(QWidget *)), this, SLOT(updateTracksDisplay(QWidget *)));
	//tabWidgetTimelineEditor->addTab(currentTimeline, "Master Timeline");
	vboxTimelineFrame->addWidget(currentTimeline);
	currentTimeline->horizontalScrollBar()->setValue(1);

	QFrame *frameTrackName = new QFrame(this);
	frameTrackName->setFrameShape(QFrame::StyledPanel);
	frameTrackName->setLayout(vboxTrackNameFrame);

	QFrame *frameTimeline = new QFrame(this);
	frameTimeline->setFrameShape(QFrame::StyledPanel);
	frameTimeline->setLayout(vboxTimelineFrame);

	QSplitter *splitterTimeline = new QSplitter(Qt::Horizontal, this);
	splitterTimeline->addWidget(frameTrackName);
	splitterTimeline->addWidget(frameTimeline);
	QList<int> sizes({ 250, 700 });
	splitterTimeline->setSizes(sizes);

	vboxTimelineEditorContainer->addWidget(splitterTimeline);
}

void TimelineEditor::addTrack(int newTrackIndex, Track *track) {
	qDebug() << "TimelineEditor::addTrack called, adding track controls, then track timeline";
	vboxTrackNameFrame->addWidget(track->getTrackControlsTimelineWidget());
    //add a rectangle to the track for the wave form, track length, etc.
    //the initial width is the width of the currnet timeline tick (based on zoom level)
    QRectF rectTrackTimeline(0,
                             ((newTrackIndex - 1) * 48) - 164,
                             currentTimeline->tickSegment->intWidth,
                             48);
    QGraphicsRectItem *graphicsRectTrackTimeline = currentTimeline->scene.addRect(rectTrackTimeline,
                                                                                  QPen("#666666"),
                                                                                  QBrush("#444444"));
	graphicsRectTrackTimeline->setZValue(newTrackIndex);
}

void TimelineEditor::setCurrentPosition(int intPos) {
	intCurrentPosition = intPos;
}

void TimelineEditor::startMainTimer() {
	//if record button pressed and track armed,
	//start armed track's audioRecorder recording
	currentTimeline->startMainTimer();
}

void TimelineEditor::stopMainTimer() {
	currentTimeline->stopMainTimer();
}

void TimelineEditor::resetMainTimer() {
	currentTimeline->resetMainTimer();
}
