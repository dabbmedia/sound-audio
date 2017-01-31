#pragma once

#include "timer.h"

#include <QApplication>
#include <QFrame>
#include <QMainWindow>
#include <QObject>
#include <QTime>

//namespace Ui {
//    class MainWindow;
//}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);

    private slots:
        void startMainTimer();
        void stopMainTimer();
        void toggleStatusbar();

    private:
        void createMainMenu();
        QWidget* createMainPlaybackControls();
        QFrame* createUpperFrame();
        QFrame* createTimelineFrame();
        QAction *viewst;
        Timer *masterTimer;
};
