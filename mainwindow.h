#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QFrame>
#include <QLCDNumber>
#include <QList>
#include <QMainWindow>
#include <QObject>
#include <QTime>
#include <QWidget>

#include "project.h"
#include "resourcebrowser.h"
#include "timelineeditor.h"
#include "timer.h"

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
        QPushButton *btnBegin;
        QPushButton *btnStop;
        QPushButton *btnPlay;
		QPushButton *btnRecord;
		QList<Project *> listProjects;
		Project *currentProject = 0;
		ResourceBrowser *resourceBrowser;
        Timer *masterTimer;

	public slots:
		void updateLcd();
		void toggleStatusbar();
		void stop();
		void restart();
		void togglePlayRecord();
		void newProject();
		void openProject();
        void addTrack();
		void showErrorMessage(QString errorMessage);

	signals:
		void signalLoadProject();

    private:
        void setupTimer();
        void createMainWindowLayout();
        void createMainMenu();
        void createMainPlaybackControls();
		void openProjectSettings(Project *project);
		void editProjectSettings(Project *project);
        QFrame* createUpperFrame();
        QFrame* createTimelineFrame();
        QAction *viewst;

	protected:
		void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
