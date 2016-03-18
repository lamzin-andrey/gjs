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

    
signals:
    
public slots:
    QString file_get_contents(QString path);
    int file_put_contents(QString path, QString data, int flag = 0);
    void exec(QString command, QString onOutput, QString onError);
    void onOutput();
    void onErrorOutput();
};

#endif // CPHPINTERFACE_H
