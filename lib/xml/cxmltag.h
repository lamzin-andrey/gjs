#ifndef CXMLTAG_H
#define CXMLTAG_H

#include <QString>
#include <QStringList>
#include <QMap>

class CXmlTag
{
public:
    CXmlTag(QString name, QMap<QString, QString> attributes, QList<CXmlTag*> childs );
    CXmlTag(QString xmlFragment);

    QList<CXmlTag*> childs;
    QMap<QString, QString> attributes;
    QString name;
};

#endif // CXMLTAG_H
