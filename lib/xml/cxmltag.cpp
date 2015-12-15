#include "cxmltag.h"

CXmlTag::CXmlTag(QString xmlFragment) {
    /**
     * берет самый левый и самый правый теги,
     *  проверяет, правда ли они (открывающий и закрывающий) и имеют одно имя
     *  если да , парсит и удаляет левый, удаляет правый
     *  все что осталось передает объекту CXml, его childs присваивает себе
     *
     *  если нет и нет правого тега, то просто парсит тег на атрибуты и имя
    */
    //самый левый тег
    xmlFragment = xmlFragment.trimmed();
    int pos = xmlFragment.indexOf('>');
    int start = pos;
    QString openTag = xmlFragment.mid(0, pos + 1);

    if (openTag[0] != '<') {
        log.append("openTag begin from '" + QString(openTag[0]) + "'!");
    }
    if (openTag[openTag.length() - 1] != '>') {
        log.append("openTag end on '" + QString(openTag[openTag.length() - 1]) + "'!");
    }
    //самый правый тег
    pos = xmlFragment.lastIndexOf('<');
    QString closeTag = xmlFragment.mid(pos, xmlFragment.length() - pos);
    if (closeTag[0] != '<') {
        log.append("closeTag begin from '" + QString(closeTag[0]) + "'!");
    }
    if (closeTag[closeTag.length() - 1] != '>') {
        log.append("closeTag end on '" + QString(closeTag[closeTag.length() - 1]) + "'!");
    }
    QString openTagName = this->_getTagName(openTag);
    QString closeTagName = this->_getTagName(closeTag);
    if (openTagName != closeTagName) {
        log.append("'" + closeTag + "' != '" + openTag + "'");
        return;
    }
    this->_parseAttributes(openTag, openTagName);
    if (closeTag.indexOf("</") == 0) {
        xmlFragment = xmlFragment.mid(start + 1, pos - start).trimmed();
        CXml cxml;
        cxml.setXmlText(xmlFragment);
        this->childs = cxml.childs;
    }
}

QString CXmlTag::_getTagName(QString s) {
    QString tagName = "";
    CXml cxml;
    for (int i = 0; i < s.length(); i++) {
        if (cxml.isNotPipe(s[i]) && s[i] != '<' && s[i] != '>' && s[i] != '/' ) {
            tagName += s[i];
        } else if (s[i] != '<') {
            break;
        }
    }
    return tagName;
}
QString CXmlTag::_parseAttributes(QString tag, QString tagName) {
   tag = tag.replace(QRegExp("^<" + tagName), "");
   tag = tag.replace(QRegExp(">$"), "");
   tag = tag.trimmed();
   QStringList attrs;
   QChar lastOpenQuote;
   bool quoteIsOpen = false;
   QString buf = "";
   CXml cxml;
   for (int i = 0; i < tag.length(); i++) {
       QChar ch = tag[i];
       if (ch == '\'' || ch == '"') {
           if (!quoteIsOpen) {
               quoteIsOpen = true;
               lastOpenQuote = ch;
           } else {
                if (lastOpenQuote == ch ) {
                    quoteIsOpen = false;
                    lastOpenQuote = QChar(0);
                }
            }
        }
        if (!quoteIsOpen) {
            if (cxml.isNotPipe(ch) && ch != '=') {
                buf += ch;
            } else {
                if (buf.length() > 0) {
                    attrs.append(buf);
                    buf = "";
                }
                if(ch == '=') {
                    attrs.append(ch);
                }
            }
        } else {
            buf += ch;
        }
    }
    if (buf.length() > 0) {
        attrs.append(buf);
    }
    int L = attrs.length();
    for (int i = 0; i < L; i++) {
        QString key = attrs[i].trimmed();
        if (key != "=") {
            if (key.length() && i + 2 < L) {
                QString sign = attrs[i + 1].trimmed();
                QString val = attrs[i + 2].trimmed();
                if (sign == "=") {
                    if (val[0] == '"' || val[0] == '\'') {
                        val = val.mid(1, val.length() - 2);
                    }
                    attributes.insert(key, val);
                    i += 2;
                } else {
                    attributes.insert(key, "");
                }
            } else if (key.length()) {
                attributes.insert(key, "");
            }
        }
    }
}


CXmlTag::CXmlTag(QString name, QMap<QString, QString> attributes, QList<CXmlTag*> childs ) {

}
