#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include "timeline.h"
#include "track.h"

#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class TimelineEditor : public QWidget
{
    Q_OBJECT

	public:
		explicit TimelineEditor(QWidget *parent = 0);
		QVBoxLayout *vboxTrackNameFrame;
		QVBoxLayout *vboxTimelineFrame;
		Timeline *currentTimeline;
		QToolButton *btnAddTrack;
		int intCurrentPosition;

	protected:
		QVBoxLayout *vboxTimelineEditorContainer;
		void createToolBar();
		void createTracksLayout();

    public slots :
		void setCurrentPosition(int intPos);
		void startMainTimer();
		void stopMainTimer();
		void resetMainTimer();
		void addTrack(int newTrackIndex, Track *track);
};

//Q_DECLARE_METATYPE(TimelineEditor);

#endif // TIMELINEEDITOR_H
