#ifndef RESOURCEBROWSER_H
#define RESOURCEBROWSER_H

#include "project.h"

#include <QList>
#include <QMainWindow>
#include <QTreeWidget>
#include <QWidget>

class ResourceBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit ResourceBrowser(QList<Project *> listProjects, QWidget *parent = 0);
    void getResourceBrowser();
	void displayProjectTree(QList<Project *> listProjects);
	QTreeWidget *treeProjects;
	QVBoxLayout *vboxTabProjects;

private:
	void readProjectSettings();

};

#endif // RESOURCEBROWSER_H
