#include "cwebpage.h"

CWebPage::CWebPage(QWidget *parent) :
    QWebPage(parent)
{
}


bool CWebPage::shouldInterruptJavaScript(){
    return false;
}

void CWebPage::javaScriptConsoleMessage( const QString & message, int lineNumber, const QString & sourceID )
{
    OS os;
    QString tempFolder = os.getTempFolderPath();
    QString data = message  + "\r\n\r\n, line: " + QString::number(lineNumber) + ", source: " + sourceID;
    //lib.qMessageBox("Locarion", tempFolder + "\\rcafe_pdf_export_error.log");
    lib.writetextfile(tempFolder  + "\\rcafe_pdf_export_error.log", data + "\r\n\r\n====================\r\n\r\n", true);
}
