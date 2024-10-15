#ifndef CMETADATA_H
#define CMETADATA_H

#include <QString>
#include <QStringList>
#include <QFile>
#include "../lib/utils.h"

class CMetadata
{
public:
    CMetadata(QString file = "", int argc = 0, char** argv = 0);
    CMetadata(QString file, QStringList args);
    QString sTitle;
    /** window buttons */
    bool min;
    bool max;
    bool close;
    bool question;

    /** win style*/
    bool onlyTop;
    bool noFrame;
    bool fullScreen;

    /** win size */
    int windowHeight;
    int windowWidth;
    bool fixedSize;

    static QString PIPE;

    QStringList getArgs();

    //TODO главное меню окна

private:
    QString _sHead;
    QString _sMenu;
    QString _getHead();
    Utils lib;
    QStringList args;

    void _setTitle(QStringList aTitle);
    void _setWinButtons(QStringList aMeta);
    int _parseNumAttr(int pos, QString s);
    void _initArgv(int argc, char** argv);
    void _initalize(QString file);

};

#endif // CMETADATA_H
