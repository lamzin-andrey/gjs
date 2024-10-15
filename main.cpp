#include "ui/cwindow.h"
#include "logic/cmetadata.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    string version = string("3.1.14");

    if (argc > 1 && string(argv[1]) == "--version") {
        cout << version << "\n";
        return 0;
    }

    QApplication a(argc, argv);
    QString path = QApplication::applicationDirPath() + "/default";
    if (argc > 1) {
        path = QString(argv[1]);
    }
    //TODO class for анализ ваших всяких вещей, типа какие иконки у окна показывать
    CMetadata data(path, argc, argv);
    CWindow w(path, data, QString(version.c_str()));
    //w.show();
    
    return a.exec();
}

