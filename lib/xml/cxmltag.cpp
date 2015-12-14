#include "cxmltag.h"

CXmlTag::CXmlTag(QString xmlFragment)
{
    /**
     * берет самый левый и самый правый теги,
     *  проверяет, правда ли они (открывающий и закрывающий) и имеют одно имя
     *  если да , парсит и удаляет левый, удаляет правый
     *  все что осталось передает объекту CXml, его childs присваивает себе
     *
     *  если нет и нет правого тега, то просто парсит тег на атрибуты и имя
    */
}

CXmlTag::CXmlTag(QString name, QMap<QString, QString> attributes, QList<CXmlTag*> childs )
{

}
