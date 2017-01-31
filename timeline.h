#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>

class Timeline : public QWidget
{
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = 0);
    QWidget *widgetTimeline;
    QWidget * getTimeline();

signals:

public slots:
};

#endif // TIMELINE_H
