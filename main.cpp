#include "ui/cwindow.h"
#include "logic/cmetadata.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    string version = "3.1.10";
    if (argc > 1) {
        string s = string(argv[1]);
        if ("--version" == s) {
            cout << version << '\n';
            return 0;
        }
    }


    QApplication a(argc, argv);
    QString path = QApplication::applicationDirPath() + "/default";


    CMetadata data(path, argc, argv);
    CWindow w(path, data, QString(version.c_str()));
    //w.show();
    
    return a.exec();
}

