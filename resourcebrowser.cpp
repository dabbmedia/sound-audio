#include "resourcebrowser.h"

#include <QTabWidget>
#include <QTreeWidget>
#include <QVBoxLayout>

ResourceBrowser::ResourceBrowser(QWidget *parent) : QWidget(parent)
{
    widgetResourceBrowser = new QWidget;
}

QWidget * ResourceBrowser::getResourceBrowser() {
    QTabWidget *tabWidgetResourceBrowser = new QTabWidget(this);

    /* Tab Projects */
    QTreeWidget *treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    treeWidget->insertTopLevelItems(0, items);

    QVBoxLayout *vboxTabProjects = new QVBoxLayout();
    vboxTabProjects->setSpacing(0);
    vboxTabProjects->setContentsMargins(0, 0, 0, 0);
    vboxTabProjects->addWidget(treeWidget);

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

    widgetResourceBrowser->setLayout(vboxResourceBrowserContainer);
    widgetResourceBrowser->setObjectName("widgetResourceBrowser");
    widgetResourceBrowser->setStyleSheet("QWidget#widgetResourceBrowser { border: 0; }");

    return widgetResourceBrowser;
}
