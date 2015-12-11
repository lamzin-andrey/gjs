#include "cphpinterface.h"

CPhpInterface::CPhpInterface(QWidget *parent) :
    QWidget(parent)
{


}
int CPhpInterface::file_put_contents(QString path, QString data, int flag) {
    bool append = flag == 1;
    return lib.writetextfile(path, data, append);
}

QString CPhpInterface::file_get_contents(QString path) {
    return lib.readtextfile(path);
}
