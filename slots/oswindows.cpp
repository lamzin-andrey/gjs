#include "os.h"

OS::OS(QObject *parent, CWebView *webView) :
    QObject(parent)
{
    this->webView = webView;
}


int OS::ShellExecuteQ(QString operation, QString path, QString params, QString directory, bool showCmdLine) {
    string sOperation = operation.toStdString();
    string sPath = path.toStdString();
    string sParams = path.toStdString();
    string sDirectory = directory.toStdString();
    int show = showCmdLine ? 1 : 0;
    Utils lib;
    //lib.qMessageBox("", "run");
    ShellExecuteA(0, (LPCSTR)sOperation.c_str(), (LPCSTR)sPath.c_str(), (LPCSTR)sParams.c_str(), (LPCSTR)sDirectory.c_str(), show);

    /*sOperation = "open";
    sPath = "notepad.exe";
    sParams = "";
    sDirectory = "";
    show = true;*/
    //ShellExecuteA(0, (LPCSTR)"open", (LPCSTR)"C:/windows/System32/notepad.exe", NULL, NULL, 1);
    return 0;
}


QString OS:: getLocalFileStartUrl() {
    return "file://localhost";
}

QString OS:: getTempFolderPath() {

    // return QApplication::applicationDirPath() + "/tmp";

    int sz = 255;
    char* buf[sz];
    for (int i = 0; i < sz; i++) {
        buf[i] = 0;
    }
    GetEnvironmentVariableA((LPSTR)"TEMP", (LPSTR)buf, sz);
    string s((char*)buf);
    QString qs = QString::fromStdString(s);
    return qs;
}


QString OS:: getHomeFolderPath() {

    // return QApplication::applicationDirPath() + "/tmp";

    int sz = 255;
    char* buf[sz];
    for (int i = 0; i < sz; i++) {
        buf[i] = 0;
    }
    GetEnvironmentVariableA((LPSTR)"HOMEPATH", (LPSTR)buf, sz);
    string s((char*)buf);
    QString qs = QString::fromStdString(s);
    return qs;
}

QString OS:: getTempDir() {
    return getTempFolderPath();
}

QString OS:: getHomeDir() {
    return getHomeFolderPath();
}
