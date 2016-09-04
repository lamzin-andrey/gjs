#ifndef OSWINDOWS_H
#define OSWINDOWS_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QByteArray>
#include "../lib/utils.h"
#include "windows.h"
#include "../ui/cwebview.h"
class OSWindows : public QObject
{
    Q_OBJECT
public:
    explicit OSWindows(QObject *parent = 0, CWebView *webView = 0);
    QString getLocalFileStartUrl();
signals:
    
public slots:
  int ShellExecuteQ(QString operation, QString path, QString params, QString directory, bool showCmdLine = false);
  QString getTempFolderPath();
private:
  CWebView *webView;
};

#endif // OSWINDOWS_H
