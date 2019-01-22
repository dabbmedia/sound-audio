#include <QFormLayout>
#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLineEdit>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QShortcut>
#include <QSplitter>
#include <QStatusBar>
#include <QTime>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QtDebug>

#include "mainwindow.h"
#include "project.h"
#include "projectsettings.h"
#include "resourcebrowser.h"
#include "timelineeditor.h"
#include "timer.h"

// Use as a controller?
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

	QCoreApplication::setOrganizationName("Dabb Media");
	QCoreApplication::setOrganizationDomain("www.dabbmedia.com");
    QCoreApplication::setApplicationName("SoundAudio");

    setupTimer();

    createMainWindowLayout();

    readSettings();

    openProject();
}

MainWindow::~MainWindow() {
	close();
}

void MainWindow::setupTimer() {
    masterTimer = new Timer;
    QThread timerThread;
    masterTimer->moveToThread(&timerThread);
    connect(&timerThread, &QThread::finished, masterTimer, &QObject::deleteLater);
//	connect(this, &Timeline::signalTimerStart, masterTimer, &Timer::startMasterTimer);
//	connect(this, &Timeline::signalTimerStop, masterTimer, &Timer::stopMasterTimer);
//	connect(this, &Timeline::signalTimerReset, masterTimer, &Timer::resetTimer);
//	connect(masterTimer, SIGNAL(signalTimerAdvanced(int)), this, SLOT(advanceTimeline(int)));
//	timerThread.start();
}

void MainWindow::createMainWindowLayout() {
    widgetTlEditor = new TimelineEditor;
    connect(widgetTlEditor->btnAddTrack, SIGNAL(clicked()), this, SLOT(addTrack()));

    createMainMenu();

    /* Layout */
    /*Main Controls layout*/
    widgetMainControls = new QWidget;
    createMainPlaybackControls();

    QFrame *frameTimelines = createTimelineFrame();

    QFrame *frameUpper = createUpperFrame();

    /* Splitter for resizing Upper and Timeline sections */
    QSplitter *splitterDevTime = new QSplitter(Qt::Vertical, this);
    splitterDevTime->addWidget(frameUpper);
    splitterDevTime->addWidget(frameTimelines);
    QList<int> sizes({250, 600});
    splitterDevTime->setSizes(sizes);

    /* Resizable section layout */
    QVBoxLayout *vboxResizable = new QVBoxLayout();
    vboxResizable->setSpacing(0);
    vboxResizable->addWidget(splitterDevTime);
    vboxResizable->setContentsMargins(0, 0, 0, 0);

    /* Main layout */
    QVBoxLayout *vboxContainer = new QVBoxLayout();
    vboxContainer->setSpacing(0);
    vboxContainer->addWidget(widgetMainControls);
    vboxContainer->addLayout(vboxResizable);
    vboxContainer->setContentsMargins(0, 0, 0, 0);

    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(vboxContainer);
    setCentralWidget(window);
}

void MainWindow::createMainMenu() {
    QAction *newa = new QAction("&New", this);
    newa->setShortcut(QKeySequence(tr("CTRL+N", "File|New")));
	
	QAction *newProject = new QAction("&New Project", this);
    newProject->setShortcut(QKeySequence(tr("CTRL+SHIFT+N")));

    QAction *open = new QAction("&Open", this);
    open->setShortcut(tr("CTRL+O"));
    
	QAction *quit = new QAction("&Quit", this);
    quit->setShortcut(tr("CTRL+Q"));

    viewst = new QAction("&View statusbar", this);
    viewst->setCheckable(true);
    viewst->setChecked(true);

    QMenu *file;
    file = menuBar()->addMenu("&File");
    file->addAction(newa);
	file->addAction(newProject);
    file->addAction(open);
    file->addSeparator();

    file->addAction(viewst);
    statusBar();
    connect(viewst, &QAction::triggered, this, &MainWindow::toggleStatusbar);

    file->addSeparator();
    file->addAction(quit);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::createMainPlaybackControls() {
	lcdTimer = new QLCDNumber;
	lcdTimer->setSegmentStyle(QLCDNumber::Flat);
	lcdTimer->setDigitCount(12);
	lcdTimer->display("00:00:00.000");

    btnBegin = new QPushButton(this);
    btnBegin->setFixedSize(24, 24);
	btnBegin->setIcon(QIcon(":/icon-beginning.svg"));
	btnBegin->setIconSize(QSize(10, 10));
	btnBegin->setShortcut(Qt::CTRL + Qt::Key_Left);
	//connect(btnBegin, SIGNAL(clicked()), widgetTlEditor->currentTimeline, SLOT(resetMainTimer()));
	connect(btnBegin, SIGNAL(clicked()), this, SLOT(restart()));

    btnStop = new QPushButton(this);
    btnStop->setFixedSize(24, 24);
	btnStop->setIcon(QIcon(":/icon-stop.svg"));
	btnStop->setIconSize(QSize(8, 8));
    //connect(btnStop, SIGNAL(clicked()), widgetTlEditor->currentTimeline, SLOT (stopMainTimer()));
	connect(btnStop, SIGNAL(clicked()), this, SLOT(stop()));

    btnPlay = new QPushButton(this);
    btnPlay->setFixedSize(24, 24);
	btnPlay->setIcon(QIcon(":/icon-play.svg"));
	btnPlay->setIconSize(QSize(8, 8));
	btnPlay->setShortcut(tr("SPACE"));
    btnPlay->setCheckable(true);
    //connect(btnPlay, SIGNAL(clicked()), widgetTlEditor->currentTimeline, SLOT (startMainTimer()));
	connect(btnPlay, SIGNAL(clicked()), this, SLOT(togglePlayRecord()));

    btnRecord = new QPushButton(this);
    btnRecord->setFixedSize(24, 24);
	btnRecord->setIcon(QIcon(":/icon-record.svg"));
	btnRecord->setIconSize(QSize(8, 8));
	btnRecord->setCheckable(true);
//    connect(btnRecord, &QPushButton::clicked, qApp, &QApplication::quit);

    QHBoxLayout *hboxMainControls = new QHBoxLayout(widgetMainControls);
//    hboxMainControls->setSpacing(8);
    hboxMainControls->addWidget(lcdTimer);
    hboxMainControls->addWidget(btnBegin);
    hboxMainControls->addWidget(btnStop);
    hboxMainControls->addWidget(btnPlay);
    hboxMainControls->addWidget(btnRecord);
    hboxMainControls->setAlignment(Qt::AlignLeft);
    hboxMainControls->addStretch(1);
    hboxMainControls->setContentsMargins(0, 0, 0, 0);

    widgetMainControls->setFixedHeight(36);
}

void MainWindow::restart() {
	if (btnRecord->isChecked()) {
		for (int i = 0; i < currentProject->tracks.size(); ++i) {
			if (currentProject->tracks.at(i)->btnArm->isChecked()) {
				currentProject->tracks.at(i)->toggleRecord();
			}
		}
	}

	widgetTlEditor->currentTimeline->resetMainTimer();

	if (btnRecord->isChecked()) {
		for (int i = 0; i < currentProject->tracks.size(); ++i) {
			if (currentProject->tracks.at(i)->btnArm->isChecked()) {
				currentProject->tracks.at(i)->toggleRecord();
			}
		}
	}
}

void MainWindow::stop() {
	if (btnRecord->isChecked()) {
		for (int i = 0; i < currentProject->tracks.size(); ++i) {
			if (currentProject->tracks.at(i)->btnArm->isChecked()) {
                currentProject->tracks.at(i)->stop();
                btnRecord->setChecked(false);
                btnPlay->setChecked(false);
			}
		}
	}

	widgetTlEditor->currentTimeline->stopMainTimer();
}

void MainWindow::togglePlayRecord() {
	for (int i = 0; i < currentProject->tracks.size(); ++i) {
		if (btnRecord->isChecked()) {
			if (currentProject->tracks.at(i)->btnArm->isChecked()) {
				currentProject->tracks.at(i)->toggleRecord();
			}
		}
        else {
			currentProject->tracks.at(i)->togglePlay();
		}
	}

	widgetTlEditor->currentTimeline->startMainTimer();
}

QFrame* MainWindow::createUpperFrame() {
    resourceBrowser = new ResourceBrowser(listProjects);

    QVBoxLayout *vboxUpperLeft = new QVBoxLayout();
    vboxUpperLeft->setSpacing(0);
    vboxUpperLeft->setContentsMargins(0, 0, 0, 0);
    vboxUpperLeft->addWidget(resourceBrowser);

    QFrame *frameUpperLeft = new QFrame(this);
    frameUpperLeft->setFrameShape(QFrame::StyledPanel);
    frameUpperLeft->setLayout(vboxUpperLeft);

    /* Devices layout*/
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(2);
    grid->setContentsMargins(0, 0, 0, 0);
//    grid->addWidget(rbMain); //devices go here?

    QFrame *frameUpperRight = new QFrame(this);
    frameUpperRight->setFrameShape(QFrame::StyledPanel);
    frameUpperRight->setLayout(grid);

    QSplitter *splitterUpper = new QSplitter(Qt::Horizontal, this);
    splitterUpper->addWidget(frameUpperLeft);
    splitterUpper->addWidget(frameUpperRight);
    QList<int> sizes({250, 600});
    splitterUpper->setSizes(sizes);

    QHBoxLayout *hboxUpper = new QHBoxLayout();
    hboxUpper->setSpacing(0);
    hboxUpper->setContentsMargins(0, 0, 0, 0);
    hboxUpper->addWidget(splitterUpper);

    QFrame *frameUpper = new QFrame(this);
    frameUpper->setFrameShape(QFrame::StyledPanel);
    frameUpper->setLayout(hboxUpper);

    return frameUpper;
}

QFrame* MainWindow::createTimelineFrame() {
    /* Timelines layout */
    QVBoxLayout *vboxTimelines = new QVBoxLayout();
    vboxTimelines->setContentsMargins(0, 0, 0, 0);

    QFrame *frameTimelines = new QFrame(this);
    frameTimelines->setFrameShape(QFrame::StyledPanel);

    /* Add timeline editor */
	connect(widgetTlEditor->currentTimeline, SIGNAL(signalDisplay()), this, SLOT(updateLcd()));
    vboxTimelines->addWidget(widgetTlEditor);

    frameTimelines->setLayout(vboxTimelines);

    return frameTimelines;
}

void MainWindow::addTrack() {
    qDebug() << "MainWindow::addTrack";
    if (currentProject) {
        currentProject->addTrack();
        if (currentProject->tracks.size() > 0) {
            widgetTlEditor->addTrack(currentProject->tracks.size(), currentProject->tracks.at(currentProject->tracks.size() - 1));
        }
    }
}

void MainWindow::updateLcd() {
	QTime t = QTime(0, 0, 0, 0).addMSecs(widgetTlEditor->currentTimeline->intCurrentPosition);
	QString stringElapsed = t.toString("hh:mm:ss.zzz");

	lcdTimer->display(stringElapsed);
}

void MainWindow::toggleStatusbar() {

  if (viewst->isChecked()) {

      statusBar()->show();
  } else {

      statusBar()->hide();
  }
}

void MainWindow::newProject() {
	Project *project = new Project;
	listProjects << project;
	resourceBrowser->displayProjectTree(listProjects);
	currentProject = project;
    openProjectSettings(project);
}

void MainWindow::openProject() {
    //if lastProject exists, set to currentProject
    //else create a new project
    if (currentProject->name == "") {
        newProject();
    } else {
        qDebug() << "project name: " << currentProject->name;
    }
	//refresh resourceBrowser project list

	//set timeline position

	//update track view

}

void MainWindow::openProjectSettings(Project *project) {
	ProjectSettings *projectSettings = new ProjectSettings(project, this);
	projectSettings->show();
	//connect(projectSettings, SIGNAL(signalProjectSaved), this, SLOT());
}

void MainWindow::editProjectSettings(Project *project) {
	ProjectSettings *projectSettings = new ProjectSettings(project, this);
	projectSettings->show();
}

void MainWindow::writeSettings() {
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	settings.beginGroup("MainWindow");
	settings.setValue("timelinePosition", widgetTlEditor->intCurrentPosition);
	settings.setValue("currentProjectFile", currentProject->file);
	settings.endGroup();

	settings.beginWriteArray("projects");
	for (int i = 0; i < listProjects.size(); ++i) {
		settings.setArrayIndex(i);
		settings.setValue("name", QVariant::fromValue(listProjects.at(i)->name));
		settings.setValue("file", QVariant::fromValue(listProjects.at(i)->file));
	}
	settings.endArray();
}

void MainWindow::readSettings() {
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	int size = settings.beginReadArray("projects");
	for (int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		Project *project = new Project(settings.value("file").toString());
		listProjects.append(project);
	}
	settings.endArray();

	settings.beginGroup("MainWindow");
	widgetTlEditor->currentTimeline->setCurrentPosition(settings.value("timeline_position", 0).toInt());
//	widgetTlEditor->currentTimeline->masterTimer->intStopPosition = settings.value("timeline_position", 0).toInt();
    masterTimer->intStopPosition = settings.value("timeline_position", 0).toInt();

	currentProject = new Project(settings.value("currentProjectFile", "").toString());
    settings.endGroup();
}

void MainWindow::showErrorMessage(QString errorMessage) {
	qDebug() << "SLOT: " << errorMessage;
	/*QMessageBox msgBox;
	msgBox.setText(errorMessage);
	msgBox.exec();*/
}

/**
 * event not triggered when click Quit from menu (or CTRL-Q),
 * only when clicking the x
 */
void MainWindow::closeEvent(QCloseEvent *event) {
	writeSettings();
	event->accept();
}
