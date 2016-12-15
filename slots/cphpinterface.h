#ifndef CPHPINTERFACE_H
#define CPHPINTERFACE_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDirIterator>
#include <QImage>
#include <QFileInfo>
#include <QRegExp>
#include <QList>
#include <QWebFrame>
#include <string>

#include "../lib/utils.h"
#include "../logic/process/cprocess.h"
#include "../ui/cwebview.h"

class CPhpInterface : public QWidget
{
    Q_OBJECT
public:
    explicit CPhpInterface(QWidget *parent = 0, CWebView *webView = 0);
private:
    Utils lib;
    //php exec procs

    bool procIsInit;
    CWebView *webView;


    CProcess * _cproc;
    QList<CProcess *> cprocList;
    unsigned int cprocId;
    
signals:
    
public slots:
    //file
    QString file_get_contents(QString path);
    int file_put_contents(QString path, QString data, int flag = 0);
    bool file_exists(QString path);
    bool is_dir(QString path);
    qint64  filesize(QString path);

    //exec
    void execCProcess(QString command, QString onFinish, QString onOutput = "", QString onError = "");
    void exec(QString command, QString onFinish, QString onOutput = "", QString onError = "");
    void onCProcessOutput(QString onOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessEmptyArguments();
    void onCProcessEmptyOutput(bool isErrorOutput);
    void onCProcessFinish(QString evaluateJavaScript, unsigned int resId);

    //file system
    QString _scandir(QString path);

    //images
    QString _getimagesize(QString path);
};

#endif // CPHPINTERFACE_H
