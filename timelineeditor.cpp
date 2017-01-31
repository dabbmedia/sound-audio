#include "timelineeditor.h"
#include "timeline.h"

#include <QComboBox>
#include <QPushButton>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

TimelineEditor::TimelineEditor(QWidget *parent) : QWidget(parent)
{
    widgetTimelineEditor = new QWidget;

    QTabWidget *tabWidgetTimelineEditor = new QTabWidget(this);

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

    QComboBox *cbSelectTimeline = new QComboBox;
    cbSelectTimeline->insertItem(1, "Master Timeline");
    cbSelectTimeline->setFixedHeight(32);
//    cbSelectTimeline->setContentsMargins(8, 2, 8, 2);
    cbSelectTimeline->setStyleSheet("QComboBox { margin-left: 16px; padding: 2px 8px; }");

    QToolButton *btnAddTimeline = new QToolButton(this);
    btnAddTimeline->setFixedSize(QSize(32, 32));
    btnAddTimeline->setIcon(QIcon(":/icon-add.svg"));
    btnAddTimeline->setToolTip("Add Timeline");
//    connect(btnClipSelect, SIGNAL (clicked()), this, SLOT (stopMainTimer()));

    QToolBar *toolBarTimelineEditor = new QToolBar;
    toolBarTimelineEditor->setIconSize(QSize(12, 12));
    toolBarTimelineEditor->addWidget(btnClipSelect);
    toolBarTimelineEditor->addWidget(btnClipSplit);
    toolBarTimelineEditor->addWidget(cbSelectTimeline);
    toolBarTimelineEditor->addWidget(btnAddTimeline);

    Timeline *timelineMaster = new Timeline;
    QWidget *currentTimeline = timelineMaster->getTimeline();

    tabWidgetTimelineEditor->addTab(currentTimeline, "Master Timeline");

    QVBoxLayout *vboxTimelineEditorContainer = new QVBoxLayout();
    vboxTimelineEditorContainer->setSpacing(0);
    vboxTimelineEditorContainer->addWidget(toolBarTimelineEditor);
    vboxTimelineEditorContainer->addWidget(tabWidgetTimelineEditor);
    vboxTimelineEditorContainer->setContentsMargins(0, 0, 0, 0);

    widgetTimelineEditor->setLayout(vboxTimelineEditorContainer);
}

QWidget * TimelineEditor::getTimelineEditor() {
    return widgetTimelineEditor;
}
