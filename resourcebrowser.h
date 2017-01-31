#ifndef RESOURCEBROWSER_H
#define RESOURCEBROWSER_H

#include <QWidget>

class ResourceBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit ResourceBrowser(QWidget *parent = 0);
    QWidget * getResourceBrowser();

protected:
    QWidget *widgetResourceBrowser;

signals:

public slots:
};

#endif // RESOURCEBROWSER_H
