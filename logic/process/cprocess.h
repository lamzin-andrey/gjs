#ifndef CPROCESS_H
#define CPROCESS_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QRegExp>

#include "../../lib/utils.h"
#include "../cmetadata.h"

class CProcess : public QWidget
{
    Q_OBJECT
public:
    explicit CProcess(unsigned int resId, QString onOutput, QString onError, QString onFinish, QWidget *parent = 0);
    
    void exec(QString command, QString workDir = "");

private:
    Utils lib;
    QProcess *_proc;
    bool _procIsInit;
    QStringList _execArgs;
    QStringList _output;
    QStringList _errors;
    unsigned int _resId;
    QString _onOutput;
    QString _onError;
    QString _onFinish;

    QString _parseCommand(QString command);
signals:
    void onOutputSg (QString onOutputEvaluateJavaScript, unsigned int resId);
    void onErrorSg  (QString, unsigned int);
    void onFinishSg (QString onFinishEvaluateJavaScript, unsigned int resId);
    void onEmptyArgumentsSg ();
    void onEmptyOutputSg(bool isErrorStream);

public slots:
    void onErrorOutput();
    void onOutput();
    void onFinish();
    
};

#endif // CPROCESS_H
