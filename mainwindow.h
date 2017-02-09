#pragma once

#include "timelineeditor.h"

#include <QApplication>
#include <QFrame>
#include <QLCDNumber>
#include <QMainWindow>
#include <QObject>
#include <QTime>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
		TimelineEditor *widgetTlEditor;
		QWidget *widgetMainControls;
		QLCDNumber *lcdTimer;

    private slots:
		void updateLcd(int intPos);
        void toggleStatusbar();

    private:
        void createMainMenu();
        void createMainPlaybackControls();
        QFrame* createUpperFrame();
        QFrame* createTimelineFrame();
        QAction *viewst;
};
