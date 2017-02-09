#include "timelineeditor.h"
#include "timeline.h"

#include <QComboBox>
#include <QPushButton>
#include <QScrollBar>
#include <QSplitter>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QtDebug>

TimelineEditor::TimelineEditor(QWidget *parent) : QWidget(parent)
{
    vboxTimelineEditorContainer = new QVBoxLayout();
    vboxTimelineEditorContainer->setSpacing(0);
    vboxTimelineEditorContainer->setContentsMargins(0, 0, 0, 0);

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

	QToolButton *btnAddTimeline = new QToolButton(this);
	btnAddTimeline->setFixedSize(QSize(32, 32));
	btnAddTimeline->setIcon(QIcon(":/icon-add.svg"));
	btnAddTimeline->setToolTip("Add Timeline");
	//    connect(btnClipSelect, SIGNAL (clicked()), this, SLOT (stopMainTimer()));

	QToolButton *btnZoomOut = new QToolButton(this);
	btnZoomOut->setText("-");
	btnZoomOut->setFixedSize(QSize(32, 32));
	btnZoomOut->setStyleSheet("QToolButton { text-align: right; }");
	btnZoomOut->setToolTip("Zoom In");
	btnZoomOut->setShortcut(Qt::CTRL + Qt::Key_Minus);
	connect(btnZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));

	QToolButton *btnZoomIn = new QToolButton(this);
	btnZoomIn->setText("+");
	btnZoomIn->setFixedSize(QSize(32, 32));
	btnZoomIn->setStyleSheet("QToolButton { right: 0; }");
	btnZoomIn->setToolTip("Zoom Out");
	btnZoomIn->setShortcut(Qt::CTRL + Qt::Key_Plus);
	connect(btnZoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));

	QToolBar *toolBarTimelineEditor = new QToolBar;
	toolBarTimelineEditor->setIconSize(QSize(12, 12));
	toolBarTimelineEditor->addWidget(btnClipSelect);
	toolBarTimelineEditor->addWidget(btnClipSplit);
	toolBarTimelineEditor->addWidget(btnAddTimeline);
	toolBarTimelineEditor->addSeparator();
	toolBarTimelineEditor->addWidget(btnZoomOut);
	toolBarTimelineEditor->addWidget(btnZoomIn);

	vboxTimelineEditorContainer->addWidget(toolBarTimelineEditor);
}

void TimelineEditor::createTracksLayout() {
	QVBoxLayout *vboxTrackNameFrame = new QVBoxLayout();
	vboxTrackNameFrame->setSpacing(0);
	vboxTrackNameFrame->setContentsMargins(0, 0, 0, 0);
	
	QVBoxLayout *vboxTimelineFrame = new QVBoxLayout();
	vboxTimelineFrame->setSpacing(0);
	vboxTimelineFrame->setContentsMargins(0, 0, 0, 0);
	vboxTimelineFrame->setAlignment(Qt::AlignTop);

	currentTimeline = new Timeline;
	connect(currentTimeline, SIGNAL(signalDisplay(int)), this, SLOT(setCurrentPosition(int)));
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

void TimelineEditor::zoomOut() {
	currentTimeline->zoomOut();
}

void TimelineEditor::zoomIn() {
	currentTimeline->zoomIn();
}

void TimelineEditor::setCurrentPosition(int intPos) {
	intCurrentPosition = intPos;
	emit signalDisplay(intPos);
}

void TimelineEditor::startMainTimer() {
	currentTimeline->startMainTimer();
}

void TimelineEditor::stopMainTimer() {
	currentTimeline->stopMainTimer();
}

void TimelineEditor::resetMainTimer() {
	currentTimeline->resetMainTimer();
}
