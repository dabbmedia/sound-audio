#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QXmlStreamWriter>

class ProjectSettings : public QDialog
{
	Q_OBJECT

public:
	ProjectSettings(QWidget *parent);
	~ProjectSettings();
	void newProject(QString dirName);
	QXmlStreamWriter xml;
	QString fileName;
	QLineEdit *lineEditName;
	QLineEdit *lineEditLocation;

private slots:
	void chooseProjectFolder();
	void saveProject();
};
