#pragma once

#include "project.h"

#include <QDialog>
#include <QLineEdit>

class ProjectSettings : public QDialog
{
	Q_OBJECT

public:
	ProjectSettings(Project *currentProject, QWidget *parent = 0);
	~ProjectSettings();
	QString fileName;
	QLineEdit *lineEditName;
	QLineEdit *lineEditLocation;
	Project *project;

private slots:
	void chooseProjectFolder();
	void saveProject();

signals:
	void signalProjectSaved();
};
