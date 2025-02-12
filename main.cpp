#include "ui/cwindow.h"
#include "logic/cmetadata.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    string version = "3.1.19";
    if (argc > 1) {
        string s = string(argv[1]);
        if (string("--version") == s) {
            //cout << version << '\n';
            MessageBoxA(0, (LPSTR)version.c_str(), "Version", 0);
            return 0;
        }
    }


    QApplication a(argc, argv);
    QString path = QApplication::applicationDirPath() + "/default";

    if (argc > 1) {
        path = QString(argv[1]);
    }


    CMetadata data(path, argc, argv);
    CWindow w(path, data, QString(version.c_str()));
    //w.show();
    
    return a.exec();
}

