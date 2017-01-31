#ifndef TIMELINEEDITOR_H
#define TIMELINEEDITOR_H

#include <QWidget>

class TimelineEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineEditor(QWidget *parent = 0);
    QWidget * getTimelineEditor();

protected:
    QWidget *widgetTimelineEditor;

signals:

public slots:
};

#endif // TIMELINEEDITOR_H
