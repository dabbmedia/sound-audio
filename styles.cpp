#include "styles.h"

#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <QLayout>

Styles::Styles(QObject *parent) : QObject(parent)
{
    qApp->setStyleSheet(""
        "QWidget {"
            "background-color: rgba(70, 70, 70, 0.8);"
            "border: 1px solid rgba(50, 50, 50, 0.8);"
            "color: #cccccc;"
            "font-family: Monospace;"
        "}"
        "QVBoxLayout, QHBoxLayout, QGridLayout, QSplitter, QTabWidget {"
            "border: 0;"
            "margin: 0;"
            "padding: 0;"
        "}"
        "QLineEdit { "
            "background-color: rgba(101, 101, 101, 0.8);"
            "color: #cccccc;"
            "border: 1px solid rgba(50, 50, 50, 0.8);"
            "border-radius: 4px;"
        "}"
        "QPushButton { "
            "background-color: rgba(101, 101, 101, 0.8);"
            "color: #cccccc;"
            "border: 1px solid rgba(50, 50, 50, 0.8);"
            "border-radius: 4px; "
        "}"
		"QPushButton:clicked, QPushButton:pressed, QPushButton:checked { "
            "background-color: rgba(55, 55, 55, 0.8);"
            "color: #cccccc;"
            "border: 1px solid rgba(50, 50, 50, 0.8);"
            "border-radius: 4px; "
        "}"
        "QTabBar {"
            "border: 0;"
            "padding: 2px 0 0 0;"
        "}");
}
