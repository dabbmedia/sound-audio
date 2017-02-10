#pragma once

#include "timelineeditor.h"

#include <QApplication>
#include <QFrame>
#include <QLCDNumber>
#include <QMainWindow>
#include <QObject>
#include <QAction>
#include <QTime>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
		~MainWindow();
		void writeSettings();
		void readSettings();
		TimelineEditor *widgetTlEditor;
		QWidget *widgetMainControls;
		QLCDNumber *lcdTimer;

    private slots:
		void updateLcd(int intPos);
        void toggleStatusbar();
		void newProject();

    private:
        void createMainMenu();
        void createMainPlaybackControls();
        QFrame* createUpperFrame();
        QFrame* createTimelineFrame();
        QAction *viewst;

	protected:
		void closeEvent(QCloseEvent *event) override;
};
