#include "resourcebrowser.h"

#include <QCoreApplication>
#include <QList>
#include <QMainWindow>
#include <QSettings>
#include <QTabWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QtDebug>

ResourceBrowser::ResourceBrowser(QList<Project *> listProjects, QWidget *parent) : QWidget(parent)
{
	getResourceBrowser();
	displayProjectTree(listProjects);
}

void ResourceBrowser::getResourceBrowser() {
	QTabWidget *tabWidgetResourceBrowser = new QTabWidget(this);
	
	/* Tab Projects */
	vboxTabProjects = new QVBoxLayout();
    vboxTabProjects->setSpacing(0);
    vboxTabProjects->setContentsMargins(0, 0, 0, 0);

    QWidget *widgetTabProjects = new QWidget;
    widgetTabProjects->setLayout(vboxTabProjects);

    /* Tab Files */
    QTreeWidget *treeWidgetFiles = new QTreeWidget();
    treeWidgetFiles->setColumnCount(1);
    QList<QTreeWidgetItem *> itemsFiles;
    for (int i = 0; i < 10; ++i)
        itemsFiles.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    treeWidgetFiles->insertTopLevelItems(0, itemsFiles);

    QVBoxLayout *vboxTabFiles = new QVBoxLayout();
    vboxTabFiles->setSpacing(0);
    vboxTabFiles->setContentsMargins(0, 0, 0, 0);
    vboxTabFiles->addWidget(treeWidgetFiles);

    QWidget *widgetTabFiles = new QWidget;
    widgetTabFiles->setLayout(vboxTabFiles);

    /* Tab Devices */
    QTreeWidget *treeWidgetDevices = new QTreeWidget();
    treeWidgetDevices->setColumnCount(1);
    QList<QTreeWidgetItem *> itemsDevices;
    for (int i = 0; i < 10; ++i)
        itemsDevices.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    treeWidgetDevices->insertTopLevelItems(0, itemsDevices);

    QVBoxLayout *vboxTabDevices = new QVBoxLayout();
    vboxTabDevices->setSpacing(0);
    vboxTabDevices->setContentsMargins(0, 0, 0, 0);
    vboxTabDevices->addWidget(treeWidgetDevices);

    QWidget *widgetTabDevices = new QWidget;
    widgetTabDevices->setLayout(vboxTabDevices);

    tabWidgetResourceBrowser->addTab(widgetTabProjects, "Projects");
    tabWidgetResourceBrowser->addTab(widgetTabFiles, "File System");
    tabWidgetResourceBrowser->addTab(widgetTabDevices, "Devices");

    QVBoxLayout *vboxResourceBrowserContainer = new QVBoxLayout();
    vboxResourceBrowserContainer->setSpacing(0);
    vboxResourceBrowserContainer->setContentsMargins(0, 0, 0, 0);
    vboxResourceBrowserContainer->addWidget(tabWidgetResourceBrowser);

    /*widgetResourceBrowser->setLayout(vboxResourceBrowserContainer);
    widgetResourceBrowser->setObjectName("widgetResourceBrowser");
    widgetResourceBrowser->setStyleSheet("QWidget#widgetResourceBrowser { border: 0; }");*/
	setLayout(vboxResourceBrowserContainer);
	setObjectName("widgetResourceBrowser");
	setStyleSheet("QWidget#widgetResourceBrowser { border: 0; }");

    //return widgetResourceBrowser;
}

void ResourceBrowser::readProjectSettings() {

	/*QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

	int size = settings.beginReadArray("projects");
	for (int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		Project *project = new Project(settings.value("projectFile").toString());
		listProjects.append(project);
	}
	settings.endArray();*/
}

void ResourceBrowser::displayProjectTree(QList<Project *> listProjects) {
	if (treeProjects) {
		vboxTabProjects->removeWidget(treeProjects);
	}

	treeProjects = new QTreeWidget();
	treeProjects->setColumnCount(1);
	treeProjects->setHeaderHidden(true);

	QList<QTreeWidgetItem *> items;
	for (int i = 0; i < listProjects.size(); ++i) {
		QTreeWidgetItem *itemProject = new QTreeWidgetItem((QTreeWidget*)0);
		Project *project = listProjects.at(i);
		QString projectName = project->name;
		itemProject->setText(0, projectName);
		items.append(itemProject);
	}

	//treeProjects->clear();
	treeProjects->insertTopLevelItems(0, items);

	vboxTabProjects->addWidget(treeProjects);
}
