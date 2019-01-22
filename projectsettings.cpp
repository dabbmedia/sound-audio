#include "project.h"
#include "projectsettings.h"

#include <QDialog>
//#include <QFile>
#include <QFileDialog>
//#include <QFileInfo>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLinkedList>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QtDebug>

ProjectSettings::ProjectSettings(Project *currentProject, QWidget *parent)
	: QDialog(parent)
{	
	project = currentProject;

	setModal(true);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::Dialog);
	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	setFixedSize(QSize(420, 500));

	QLabel *labelName = new QLabel(tr("Name:"));
	labelName->setStyleSheet("QLabel { border: 0; background-color: transparent; }");
	
	lineEditName = new QLineEdit;
	lineEditName->setFixedHeight(20);
	lineEditName->setText("testing");

	QLabel *labelLocation = new QLabel(tr("Location:"));
	labelLocation->setStyleSheet("QLabel { border: 0; background-color: transparent; }");
	
	lineEditLocation = new QLineEdit;
	lineEditLocation->setFixedHeight(20);
    lineEditLocation->setText(QDir::homePath());

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

void ProjectSettings::chooseProjectFolder() {
    QString defaultDirectory = QDir::homePath();
//    defaultDirectory.append("/Documents/Projects");

    QString dirName = QFileDialog::getExistingDirectory(this,
                                                        tr("New Project"),
                                                        defaultDirectory,
                                                        QFileDialog::ShowDirsOnly);
	if (dirName.isEmpty())
		return;

	QDir dir(dirName);
	if (!dir.exists()) {
		QMessageBox::warning(this, tr("SoundAudio Project"),
			tr("Directory does not exist %1:\n%2.")
			.arg(dirName));
		return;
	}

    lineEditLocation->setText(defaultDirectory);
}

void ProjectSettings::saveProject() {
	QDir dir(lineEditLocation->text());
	if (!dir.exists()) {
		QMessageBox::warning(this, tr("SoundAudio Project"),
			tr("Directory does not exist %1:\n%2.")
			.arg(lineEditLocation->text()));
		return;
	}

	project->name = lineEditName->text();
	project->file = lineEditLocation->text() + QString("/") + lineEditName->text() + ".project";

	QFileInfo fileInfo(project->file);
	project->path = fileInfo.absolutePath();

	project->writeProjectSettings();

	emit signalProjectSaved();

	accept();
}
