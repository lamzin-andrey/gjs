#ifndef OS_H
#define OS_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QByteArray>
#include "../lib/utils.h"
#include "windows.h"
#include "../ui/cwebview.h"
class OS : public QObject
{
    Q_OBJECT
public:
    explicit OS(QObject *parent = 0, CWebView *webView = 0);
    QString getLocalFileStartUrl();
signals:
    
public slots:
  int ShellExecuteQ(QString operation, QString path, QString params, QString directory, bool showCmdLine = false);
  QString getTempFolderPath();
  QString getTempDir();
private:
  CWebView *webView;
};

#endif // OS_H
