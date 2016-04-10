#ifndef CPHPINTERFACE_H
#define CPHPINTERFACE_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QRegExp>
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
    QProcess *proc;
    bool procIsInit;
    CWebView *webView;
    QString jsOnOutput;
    QString jsOnErrorOutput;
    QStringList execArgs;
    QString parseCommand(QString command);

    //CProcess usage
    CProcess * _cproc;
    
signals:
    
public slots:
    QString file_get_contents(QString path);
    int file_put_contents(QString path, QString data, int flag = 0);
    void exec(QString command, QString onOutput, QString onError);
    void onOutput();
    void onErrorOutput();

    //CProcess usage
    void execCProcess(QString command, QString onFinish, QString onOutput, QString onError);
    void onCProcessOutput(QString onOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessEmptyArguments();
    void onCProcessEmptyOutput(bool isErrorOutput);
    void onCProcessFinish(QString evaluateJavaScript, unsigned int resId);
};

#endif // CPHPINTERFACE_H
