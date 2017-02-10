#include "projectsettings.h"

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QXmlStreamWriter>
#include <QtDebug>

ProjectSettings::ProjectSettings(QWidget *parent)
	: QDialog(parent)
{	
	setModal(true);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::Dialog);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	setFixedSize(QSize(420, 500));

	QLabel *labelName = new QLabel(tr("Name:"));
	labelName->setStyleSheet("QLabel { border: 0; background-color: transparent; }");
	
	lineEditName = new QLineEdit;
	lineEditName->setFixedHeight(20);

	QLabel *labelLocation = new QLabel(tr("Location:"));
	labelLocation->setStyleSheet("QLabel { border: 0; background-color: transparent; }");
	
	lineEditLocation = new QLineEdit;
	lineEditLocation->setFixedHeight(20);

	QPushButton *btnLocation = new QPushButton("...", this);
	btnLocation->setFixedSize(QSize(24, 20));
	connect(btnLocation, SIGNAL(clicked()), this, SLOT(chooseProjectFolder()));

	QPushButton *btnSave = new QPushButton("Save", this);
	btnSave->setFixedSize(QSize(36, 28));
	connect(btnSave, SIGNAL(clicked()), this, SLOT(saveProject()));

	QHBoxLayout *hboxLayout = new QHBoxLayout;
	hboxLayout->addWidget(lineEditLocation);
	hboxLayout->addWidget(btnLocation);

	QFormLayout *formLayout = new QFormLayout;
	formLayout->addRow(labelName, lineEditName);
	formLayout->addRow(labelLocation, hboxLayout);

	QVBoxLayout *vboxLayout = new QVBoxLayout;
	vboxLayout->addLayout(formLayout);
	vboxLayout->addWidget(btnSave);

	setLayout(vboxLayout);

	setWindowTitle(tr("Project Settings"));

}

ProjectSettings::~ProjectSettings()
{
}

void ProjectSettings::newProject(QString dirName)
{
	QString fileName = dirName + "/" + lineEditName->text() + ".project";
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		qDebug() << "could not open file " << fileName;
	}

	xml.setDevice(&file);
	xml.setAutoFormatting(true);
	xml.writeStartDocument();

	xml.writeStartElement("project");

	QFileInfo fileInfo(fileName);
	QString strProjectName = fileInfo.baseName();
	QString strProjectPath = fileInfo.absolutePath();

	if (strProjectName.isEmpty() == false && strProjectPath.isEmpty() == false) {
		xml.writeStartElement("name");
		xml.writeCharacters(strProjectName);
		xml.writeEndElement(); //name
		
		xml.writeStartElement("path");
		xml.writeCharacters(strProjectPath);
		xml.writeEndElement(); //path
	}

	xml.writeEndDocument();
}

void ProjectSettings::chooseProjectFolder() {
	/*QString fileName =
		QFileDialog::getSaveFileName(this, tr("New Project"),
			QDir::currentPath(),
			tr("SoundAudio Project Files (*.project)"));*/
	QString dirName =
		QFileDialog::getExistingDirectory(this, tr("New Project"), QDir::currentPath());
	if (dirName.isEmpty())
		return;

	QDir dir(dirName);
	if (!dir.exists()) {
		QMessageBox::warning(this, tr("SoundAudio Project"),
			tr("Directory does not exist %1:\n%2.")
			.arg(dirName));
		return;
	}

	lineEditLocation->setText(dirName);
}

void ProjectSettings::saveProject() {
	QDir dir(lineEditLocation->text());
	if (!dir.exists()) {
		QMessageBox::warning(this, tr("SoundAudio Project"),
			tr("Directory does not exist %1:\n%2.")
			.arg(lineEditLocation->text()));
		return;
	}

	newProject(lineEditLocation->text());
	accept();
}
