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
    ShellExecuteA(0, (LPCSTR)sOperation.c_str(), (LPCSTR)sPath.c_str(), (LPCSTR)sParams.c_str(), (LPCSTR)sDirectory.c_str(), show);
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
