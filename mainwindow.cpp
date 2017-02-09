#include "mainwindow.h"
#include "resourcebrowser.h"
#include "timelineeditor.h"

#include <QFormLayout>
#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QPushButton>
#include <QShortcut>
#include <QSplitter>
#include <QStatusBar>
#include <QTime>
#include <QVBoxLayout>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

	widgetTlEditor = new TimelineEditor;

    createMainMenu();

    /* Layout */
    /*Main Controls layout*/
	widgetMainControls = new QWidget;
	createMainPlaybackControls();

    QFrame *frameUpper = createUpperFrame();
    QFrame *frameTimelines = createTimelineFrame();

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

//    setLayout(vboxContainer);
    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(vboxContainer);

    // Set QWidget as the central layout of the main window
    setCentralWidget(window);
}

void MainWindow::createMainMenu() {
    QAction *newa = new QAction("&New", this);
    newa->setShortcut(QKeySequence(tr("CTRL+N", "File|New")));
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
	//QHBoxLayout *hbox = new QHBoxLayout(this);
	//hbox->setContentsMargins(10, 2, 0, 0);

	lcdTimer = new QLCDNumber;
	lcdTimer->setSegmentStyle(QLCDNumber::Flat);
	lcdTimer->setDigitCount(12);
	lcdTimer->display("00:00:00.000");

    QPushButton *btnBegin = new QPushButton(this);
    btnBegin->setFixedSize(24, 24);
	btnBegin->setIcon(QIcon(":/icon-beginning.svg"));
	btnBegin->setIconSize(QSize(10, 10));
	btnBegin->setShortcut(Qt::CTRL + Qt::Key_Left);
	connect(btnBegin, SIGNAL(clicked()), widgetTlEditor, SLOT(resetMainTimer()));

    QPushButton *btnStop = new QPushButton(this);
    btnStop->setFixedSize(24, 24);
	btnStop->setIcon(QIcon(":/icon-stop.svg"));
	btnStop->setIconSize(QSize(8, 8));
    connect(btnStop, SIGNAL(clicked()), widgetTlEditor, SLOT (stopMainTimer()));

    QPushButton *btnPlay = new QPushButton(this);
    btnPlay->setFixedSize(24, 24);
	btnPlay->setIcon(QIcon(":/icon-play.svg"));
	btnPlay->setIconSize(QSize(8, 8));
	btnPlay->setShortcut(tr("SPACE"));
    connect(btnPlay, SIGNAL(clicked()), widgetTlEditor, SLOT (startMainTimer()));

    QPushButton *btnRecord = new QPushButton(this);
    btnRecord->setFixedSize(24, 24);
	btnRecord->setIcon(QIcon(":/icon-record.svg"));
	btnRecord->setIconSize(QSize(8, 8));
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

QFrame* MainWindow::createUpperFrame() {
    ResourceBrowser *resourceBrowser = new ResourceBrowser;
    QWidget *rbMain = resourceBrowser->getResourceBrowser();

    QVBoxLayout *vboxUpperLeft = new QVBoxLayout();
    vboxUpperLeft->setSpacing(0);
    vboxUpperLeft->setContentsMargins(0, 0, 0, 0);
    vboxUpperLeft->addWidget(rbMain);

    QFrame *frameUpperLeft = new QFrame(this);
    frameUpperLeft->setFrameShape(QFrame::StyledPanel);
    frameUpperLeft->setLayout(vboxUpperLeft);

    /* Devices layout*/
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(2);
    grid->setContentsMargins(0, 0, 0, 0);
//    grid->addWidget(rbMain);

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
	connect(widgetTlEditor, SIGNAL(signalDisplay(int)), this, SLOT(updateLcd(int)));
    vboxTimelines->addWidget(widgetTlEditor);

    frameTimelines->setLayout(vboxTimelines);

    return frameTimelines;
}

void MainWindow::updateLcd(int intPos) {
	qDebug() << "MainWindow::updateLcd";
	QTime t = QTime(0, 0, 0, 0).addMSecs(intPos);
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
