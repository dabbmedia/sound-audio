#-------------------------------------------------
#
# Project created by QtCreator 2017-01-28T15:07:44
#
#-------------------------------------------------

#QT       += core gui multimedia
QT += multimedia

#win32:INCLUDEPATH += $$PWD

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundAudio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    mainwindow.cpp \
    timer.cpp \
    styles.cpp \
    timeline.cpp \
    timelineeditor.cpp \
    resourcebrowser.cpp \
    timelinemarker.cpp \
    timelineticksegment.cpp \
    track.cpp \
    trackcontrolstimeline.cpp \
    project.cpp \
    projectsettings.cpp \
    trackaudiolevel.cpp

HEADERS  += \
    mainwindow.h \
    timer.h \
    styles.h \
    timeline.h \
    timelineeditor.h \
    resourcebrowser.h \
    project.h \
    projectsettings.h \
    timelinemarker.h \
    timelineticksegment.h \
    track.h \
    trackcontrolstimeline.h \
    trackaudiolevel.h

FORMS    +=

#target.path = $$[QT_INSTALL_EXAMPLES]/multimedia/soundaudio
#INSTALLS += target

QT+=widgets

DISTFILES += \
    icon-add.svg \
    icon-arrow-select.svg \
    icon-split.svg \
    icon-beginning.svg \
    icon-pause.svg \
    icon-play.svg \
    icon-record.svg \
    icon-stop.svg

RESOURCES += \
    resources.qrc
