#include "cphpinterface.h"

CPhpInterface::CPhpInterface(QWidget *parent, CWebView *webView) :
    QWidget(parent)
{
    procIsInit = false;
    this->webView = webView;





}

int CPhpInterface::file_put_contents(QString path, QString data, int flag) {
    bool append = flag == 1;
    return lib.writetextfile(path, data, append);
}

QString CPhpInterface::file_get_contents(QString path) {
    return lib.readtextfile(path);
}

void CPhpInterface::execCProcess(QString command, QString onFinish, QString onOutput, QString onError) {
    if (!procIsInit) {
        _cproc = new CProcess(1, onOutput, onError, onFinish, this);
        connect(_cproc, SIGNAL(onOutputSg(QString, unsigned int)),
                  this, SLOT(onCProcessOutput(QString , unsigned int )));
        connect(_cproc,
                SIGNAL(
                    onErrorSg(QString, unsigned int)),
                this, SLOT(
                    onCProcessErrorOutput(QString, unsigned int))
               );
        connect(_cproc, SIGNAL(onEmptyArgumentsSg()),
                this, SLOT(onCProcessEmptyArguments()));

        connect(_cproc, SIGNAL(onEmptyOutputSg(bool)),
                this, SLOT(onCProcessEmptyOutput(bool)) );

        connect(_cproc, SIGNAL(onFinishSg(QString, unsigned int)),
                this, SLOT(onCProcessFinish(QString, unsigned int)) );
    }
    _cproc->exec(command);
}

void CPhpInterface::onCProcessOutput(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessOutput!");
        this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(evaluateJavaScript);
}

void CPhpInterface::onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessERROutput!");
    this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(onErrorOutputEvaluateJavaScript);
}

void CPhpInterface::onCProcessEmptyArguments() {
    this->webView->page()->currentFrame()->evaluateJavaScript("alert('OnEmptyArgs')");
}

void CPhpInterface::onCProcessEmptyOutput(bool isErrorOutput) {
    QString s = "alert('OnEmptyOut')";
    if (isErrorOutput) {
        s = "alert('OnEmptyErrOut')";
    }
    this->webView->page()->currentFrame()->evaluateJavaScript(s);
}
void CPhpInterface::onCProcessFinish(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessFinish(" + evaluateJavaScript + ")");
    this->webView->page()->currentFrame()->evaluateJavaScript(evaluateJavaScript);
}

//=========================deprecated===================================

void CPhpInterface::exec(QString command, QString onOutput, QString onError) {
    this->jsOnOutput = onOutput;
    this->jsOnErrorOutput = onError;
    QString execPath = parseCommand(command);
    //this->webView->page()->currentFrame()->evaluateJavaScript(jsOnOutput + "('" + execArgs.join(',')  + "');");

    if (execPath.trimmed() == "") {
        this->webView->page()->currentFrame()->evaluateJavaScript("alert('OnEmptyARg')");
        return;
    }
    if (procIsInit) {
        proc->close();
    } else {
        proc = new QProcess;
        proc->setReadChannel(QProcess::StandardOutput);
        //proc->setReadChannel(QProcess::StandardError);
        proc->setEnvironment(QProcess::systemEnvironment());
        connect( proc, SIGNAL(readyReadStandardOutput()), this, SLOT(onOutput()) );
        connect( proc, SIGNAL(readyReadStandardError()), this, SLOT(onErrorOutput()) );
        procIsInit = true;
    }
    proc->start(execPath, execArgs);
}
void CPhpInterface::onOutput() {
        if ( !proc->isReadable() ) {
            this->webView->page()->currentFrame()->evaluateJavaScript("alert('empty output');");
            return;
        }
        QByteArray *ba = new QByteArray();
        *ba = proc->readAllStandardOutput();

        QString s = QString::fromUtf8(ba->data()).replace('\n', "\\n");

       // lib.qMessageBox("ss", s);
        //this->webView->page()->currentFrame()->evaluateJavaScript(jsOnOutput + "('" +  ba->data() + "');");
        this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(jsOnOutput + "('" + s + "');");
}

void CPhpInterface::onErrorOutput() {
        if ( !proc->isReadable() ) {
            this->webView->page()->currentFrame()->evaluateJavaScript("alert('Unable read error stream');");
            return;
        }
        QByteArray *ba = new QByteArray();
        *ba = proc->readAllStandardError();
        QString s = QString(ba->data()).replace('\n', "\\n");;
        //this->webView->page()->currentFrame()->evaluateJavaScript(jsOnErrorOutput + "('" + s + "');");
        this->webView->page()->currentFrame()->evaluateJavaScript(jsOnErrorOutput + "('" +  s + "');");
}

QString CPhpInterface::parseCommand(QString command) {
    QRegExp re("\\s");
    QStringList ls = command.split(re);
    execArgs.clear();
    QString result = ls[0].trimmed();
    for (int i = 1; i < ls.size(); i++) {
        execArgs.append(ls[i].trimmed());
    }
    return result;
}
