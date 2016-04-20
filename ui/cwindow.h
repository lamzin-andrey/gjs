#ifndef CLOADERDLG_H
#define CLOADERDLG_H

#include <QMainWindow>
#include <QtGui>
#include <QHBoxLayout>
#include "cwebview.h"
#include <QtWebKitWidgets/QWebFrame>
#include <QTimer>
#include <QScreen>
#include <QDesktopWidget>
#include "../lib/utils.h"
#include "../slots/cphpinterface.h"
#include "../logic/cmetadata.h"


class CMetadata;

class CWindow : public QMainWindow
{
    Q_OBJECT
public:
    CWindow(QString appDir, CMetadata metadata, QWidget *parent = 0);
    ~CWindow();
    void loadImages(bool flag);
    void stop();
    void getURL(QString url, bool writeresult = true);
    void fixSize();
    void setHtml(QString s);
    void js(QString script);
    QString currentHtml();
    QString currentText();
    void addObject(QObject* object, QString jsName);

    QString html;
 private:
    CWebView * wv;
    bool loading;
    QString lastUrl;
    unsigned int counttry;
    Utils lib;
    bool writeresult;
    QString workdir;    //folder runned app
    CPhpInterface *php; //Widget реализующий php like интерфейс для работы с файлами (возможно в будущем не только)
    CMetadata metadata;

    QTimer *timer;      //переменные изменения размера окна
    bool resized;
 private slots:
    void onLoad(bool success);
 public slots:
    QString appDir();
    QString getLineDelimeter();
    void setLineDelimeter(QString  pipe);
    void onTimer(QPrivateSignal);

 signals:
    void loadComplete();
    void errorConnect(QString msg);
};

#endif // CLOADERDLG_H

