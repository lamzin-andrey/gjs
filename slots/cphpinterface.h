#ifndef CPHPINTERFACE_H
#define CPHPINTERFACE_H

#include <QWidget>
#include <QProcess>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDirIterator>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QRegExp>
#include <QList>
#include <QWebFrame>
#include <QCryptographicHash>
#include <string>
#include <stdio.h>

#include "../lib/utils.h"
#include "../lib/utilsstd.h"
#include "../logic/process/cprocess.h"
#include "../ui/cwebview.h"

class CPhpInterface : public QWidget
{
    Q_OBJECT
public:
    explicit CPhpInterface(QWidget *parent = 0, CWebView *webView = 0);
private:
    Utils lib;
    UtilsStd libStd;
    //php exec procs

    bool procIsInit;
    CWebView *webView;


    CProcess * _cproc;
    QList<CProcess *> cprocList;
    unsigned int cprocId;

    // files work
    QList<FILE *> fileHandlersList;
    unsigned int fileHandlerState[255];
    FILE *getFreeFile(QString filename, QString mode, bool &success, unsigned int &idx);

    QString qDirIteratorLastPath;
    bool qDirIteratorIsInit;
    QDirIterator *qDirIterator;
    
signals:
    
public slots:
    //file
    QString file_get_contents(QString path);
    int file_put_contents(QString path, QString data, int flag = 0);
    bool file_exists(QString path);
    bool is_dir(QString path);
    qint64  filesize(QString path);
    bool unlink(QString path);
    bool mkdir(QString path);

    //exec
    unsigned int execCProcess(QString command, QString onFinish, QString onOutput = "", QString onError = "");
    unsigned int exec(QString command, QString onFinish, QString onOutput = "", QString onError = "");
    //пытался на основании QProcess state определять, в линуксе точно безуспешно
    bool isRun(unsigned int n);
    //идентификатор системного процесса
    unsigned int getSysId(unsigned int n);
    void onCProcessOutput(QString onOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId);
    void onCProcessEmptyArguments();
    void onCProcessEmptyOutput(bool isErrorOutput);
    void onCProcessFinish(QString evaluateJavaScript, unsigned int resId);

    //file system
    QString _scandir(QString path);

    int  open(QString filename, QString mode);
    bool close(unsigned int fileId);
    QString gets(unsigned int fileId);
    bool puts(unsigned int fileId, QString s);
    bool eof(unsigned int fileId);
    /*QString fgetc(unsigned int fileId);
    bool fputc(unsigned int fileId, QString s);
    bool fputc(unsigned int fileId, char c);
    bool fseek(unsigned int fileId, unsigned int pos, unsigned int mode);
    unsigned int fgetb(unsigned int fileId);
    bool fgetbytes(unsigned int fileId, QList<unsigned int> buffer);*/

    void replaceInFile(QString filename, QString search, QString replace, QString outfile);

    // partDir
    QStringList partDir(QString path, unsigned int sz, bool reset = false);
    // end partDir

    // hashes
    QString md5(QString s);
    QString md5_file(QString filename);

};

#endif // CPHPINTERFACE_H
