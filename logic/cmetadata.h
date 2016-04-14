#ifndef CMETADATA_H
#define CMETADATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include "../lib/utils.h"

class CMetadata
{
public:
    CMetadata(QString file = "");
    QString sTitle;
    /** window buttons */
    bool min = true;
    bool max = true;
    bool close = true;
    bool question = false;

    /** win style*/
    bool onlyTop = false;
    bool noFrame = false;
    bool fullScreen = false;

    static QString PIPE;

    //TODO главное меню окна

private:
    QString _sHead;
    QString _sMenu;
    QString _getHead();
    Utils lib;

    void _setTitle(QStringList aTitle);
    void _setWinButtons(QStringList aMeta);

};

#endif // CMETADATA_H
