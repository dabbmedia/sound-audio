#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include "timeline.h"

#include <QVBoxLayout>
#include <QWidget>

class TimelineEditor : public QWidget
{
    Q_OBJECT
	public:
		explicit TimelineEditor(QWidget *parent = 0);
		Timeline *currentTimeline;
		int intCurrentPosition;

	protected:
		QVBoxLayout *vboxTimelineEditorContainer;
		void createToolBar();
		void createTracksLayout();

	signals:
		void signalDisplay(int intPos);

	public slots :
		void zoomOut();
		void zoomIn();
		void setCurrentPosition(int intPos);
		void startMainTimer();
		void stopMainTimer();
		void resetMainTimer();
};

#endif // TIMELINEEDITOR_H
