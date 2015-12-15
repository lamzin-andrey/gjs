#ifndef CXMLTAG_H
#define CXMLTAG_H

#include <QString>
#include <QStringList>
#include <QMap>
#include "../utils.h"
#include "cxml.h"

class CXml;

class CXmlTag
{
public:
    CXmlTag(QString name, QMap<QString, QString> attributes, QList<CXmlTag*> childs );
    CXmlTag(QString xmlFragment);

    QList<CXmlTag*> childs;
    QMap<QString, QString> attributes;
    QString name;
    Utils lib;
    QStringList log;

private:
    QString _getTagName(QString s);
    QString _parseAttributes(QString tag, QString tagName);
};

#endif // CXMLTAG_H

