#ifndef CPHPINTERFACE_H
#define CPHPINTERFACE_H

#include <QWidget>
#include "../lib/utils.h"

class CPhpInterface : public QWidget
{
    Q_OBJECT
public:
    explicit CPhpInterface(QWidget *parent = 0);
private:
    Utils lib;
    
signals:
    
public slots:
    QString file_get_contents(QString path);
    int file_put_contents(QString path, QString data, int flag = 0);
};

#endif // CPHPINTERFACE_H
