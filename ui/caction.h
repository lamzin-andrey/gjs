#ifndef CACTION_H
#define CACTION_H

#include <QAction>
#include <QString>
#include <QObject>

#include "../lib/utils.h"

class CAction : public QObject
{
    Q_OBJECT
public:
    CAction(QString text, QString jsAction, QAction* qaction, int x, int y);
    QAction* qaction;
    int x;
    int y;

private:
    QString _text;
    QString _jsAction;
    Utils lib;
    
    
signals:
    void triggeredExt(QString, QString);

public slots:
    void triggered();
};

#endif // CACTION_H


