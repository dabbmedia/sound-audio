#include "timeline.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

Timeline::Timeline(QWidget *parent) : QWidget(parent)
{
    /* add a splitter to resize between
     * track names and timeline sections */
    QVBoxLayout *vboxTimelineFrame = new QVBoxLayout();
    vboxTimelineFrame->setSpacing(0);
    vboxTimelineFrame->setContentsMargins(0, 0, 0, 0);

    QFrame *frameTrackName = new QFrame(this);
    frameTrackName->setFrameShape(QFrame::StyledPanel);
    frameTrackName->setLayout(vboxTimelineFrame);

    QFrame *frameTimeline = new QFrame(this);
    frameTimeline->setFrameShape(QFrame::StyledPanel);
    frameTimeline->setLayout(vboxTimelineFrame);

    QSplitter *splitterTimeline = new QSplitter(Qt::Horizontal, this);
    splitterTimeline->addWidget(frameTrackName);
    splitterTimeline->addWidget(frameTimeline);
    QList<int> sizes({350, 600});
    splitterTimeline->setSizes(sizes);

    QVBoxLayout *vboxTimelineContainer = new QVBoxLayout();
    vboxTimelineContainer->setSpacing(0);
    vboxTimelineContainer->addWidget(splitterTimeline);
    vboxTimelineContainer->setContentsMargins(0, 0, 0, 0);

    widgetTimeline = new QWidget;
    widgetTimeline->setLayout(vboxTimelineContainer);
}

QWidget * Timeline::getTimeline() {
    return widgetTimeline;
}
