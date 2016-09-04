#include "oswindows.h"

OSWindows::OSWindows(QObject *parent, CWebView *webView) :
    QObject(parent)
{
    this->webView = webView;
}


int OSWindows::ShellExecuteQ(QString operation, QString path, QString params, QString directory, bool showCmdLine) {
    string sOperation = operation.toStdString();
    string sPath = path.toStdString();
    string sParams = path.toStdString();
    string sDirectory = directory.toStdString();
    int show = showCmdLine ? 1 : 0;
    Utils lib;
    lib.qMessageBox("", "run");
    ShellExecute(0, (LPCWSTR)sOperation.c_str(), (LPCWSTR)sPath.c_str(), (LPCWSTR)sParams.c_str(), (LPCWSTR)sDirectory.c_str(), show);
    return 0;
}


QString OSWindows:: getLocalFileStartUrl() {
    return "file://localhost";
}

QString OSWindows:: getTempFolderPath() {
    int sz = 255;
    char* buf[sz];
    GetEnvironmentVariableA((LPSTR)"TEMP", (LPSTR)buf, sz);
    string s((char*)buf);
    QString qs = QString::fromStdString(s);
    return qs;
}
