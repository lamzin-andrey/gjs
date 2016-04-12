#include "cphpinterface.h"

CPhpInterface::CPhpInterface(QWidget *parent, CWebView *webView) :
    QWidget(parent)
{
    procIsInit = false;
    this->webView = webView;
    cprocId = 0;
}

int CPhpInterface::file_put_contents(QString path, QString data, int flag) {
    bool append = flag == 1;
    return lib.writetextfile(path, data, append);
}

QString CPhpInterface::file_get_contents(QString path) {
    return lib.readtextfile(path);
}
void CPhpInterface::exec(QString command, QString onFinish, QString onOutput, QString onError) {
    this->execCProcess(command, onFinish, onOutput, onError);
}

void CPhpInterface::execCProcess(QString command, QString onFinish, QString onOutput, QString onError) {
    //if (!procIsInit) {
    cprocId++;
    CProcess * proc = new CProcess(cprocId, onOutput, onError, onFinish, this);
    connect(proc, SIGNAL(onOutputSg(QString, unsigned int)),
                  this, SLOT(onCProcessOutput(QString , unsigned int )));
        connect(proc,
                SIGNAL(
                    onErrorSg(QString, unsigned int)),
                this, SLOT(
                    onCProcessErrorOutput(QString, unsigned int))
               );
        connect(proc, SIGNAL(onEmptyArgumentsSg()),
                this, SLOT(onCProcessEmptyArguments()));

        connect(proc, SIGNAL(onEmptyOutputSg(bool)),
                this, SLOT(onCProcessEmptyOutput(bool)) );

        connect(proc, SIGNAL(onFinishSg(QString, unsigned int)),
                this, SLOT(onCProcessFinish(QString, unsigned int)) );
    //}
    proc->exec(command);
    cprocList.append(proc);

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

