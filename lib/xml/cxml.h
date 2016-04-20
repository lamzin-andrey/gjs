#ifndef CXML_H
#define CXML_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QRegExp>

#include "cxmltag.h"
#include "../utils.h"

class CXmlTag;

class CXml
{
public:
    CXml(QString file = "");
    bool setXmlText(QString xml);
    bool isNotPipe(QChar ch);

    QList<CXmlTag*> childs;
    bool success;
    QStringList log;

private:
    Utils lib;

    QString _trim(QString s);
    QString _getCloseTagName(QString xml, int pos);
    QString _getOpenTagName(QString currentTagName, QString def);
    QString _closeCurrentTag(QString currentTagName, QString openTagName, QString def);

};

#endif // CXML_H

