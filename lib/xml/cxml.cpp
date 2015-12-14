#include "cxml.h"

CXml::CXml(QString file){
    QString s = lib.readtextfile(file, true);
    if (s.length()) {
        success = setXmlText(s);
    } else {
        success = false;
    }
}
/**
 * Тут прежде всего проверяем xml на валидность
 * Заодно собираем теги верхнего уровня в childs
*/
bool CXml::setXmlText(QString xml) {
    xml = _trim(xml);
    log.clear();
    bool tagLeftIsOpen = false;
    bool tagRightIsOpen = false;
    bool inTagBody = false;     //true когда внутри <t></t>
    bool inTagDefine = false;    //true когда внутри <t> или внутри </t>
    bool quoteIsOpen = false;
    int level = 0;
    int currentLine = 0;
    int currentSymbol = 0;
    QChar lastOpenQuote;

    QString rawTag;
    bool started = false; //true если хоть один тег был открыт

    int L = xml.length();
    QString currentTagName = "";
    QString def = "/"; //12.12.2015.2015-12.12 12:37:61";
    bool currentNameIsComplete = false;
    for (int i = 0; i < L; i++) {
        QChar ch = xml[i];
        if (started) {
            rawTag += ch;
        }
        if (ch == '\n') {
            currentLine++;
            currentSymbol = 0;
        }

        if ( inTagDefine && (ch == '\'' || ch == '"')) {
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

        if (!quoteIsOpen && ch == '<') {
            if (tagLeftIsOpen || tagRightIsOpen) {
                log.push_front("Invalid symbol '<' at line " + QString::number(currentLine) + ", symbol " + QString::number(currentSymbol));
                return false;
            }
            inTagDefine = true;
            if (i + 1 < L && xml[i + 1] == '/') {
                tagRightIsOpen = true;
            } else {
                tagLeftIsOpen = true;
                if (currentTagName.length() > 0) {
                    currentTagName += def;
                }
                if (!started) {
                    rawTag += ch;
                }
                started = true;
            }
        }
        if (inTagDefine && tagLeftIsOpen) {
            if (!quoteIsOpen && !currentNameIsComplete && ch != '<' && ch != '>') {
                if (_isNotPipe(ch)) {
                    currentTagName += ch;
                } else {
                    currentNameIsComplete = true;
                }
            }
        }
        if (!quoteIsOpen && ch == '>') {
            /*bad logic! if (tagLeftIsOpen || tagRightIsOpen) {
                log.insert("Invalid symbol '>' at line " + QString::number(currentLine) + ", symbol " + QString::number(currentSymbol));
                return false;
            }*/
            inTagDefine = false;
            if (tagLeftIsOpen) {
                tagLeftIsOpen = false;
                currentNameIsComplete = false; //чтобы можно было добавить разделитель
                level++;
            }
            if (tagRightIsOpen) {
                tagRightIsOpen = false;
                QString closeTagName = _getCloseTagName(xml, i);
                QString openTagName  = _getOpenTagName(currentTagName, def);
                if (closeTagName != openTagName) {
                    QString _currentTagName = currentTagName;
                    int _level = level;
                    while ( closeTagName != openTagName ) {
                        _currentTagName = _closeCurrentTag(_currentTagName, openTagName, def);
                        _level--;
                        openTagName  = _getOpenTagName(_currentTagName, def);
                        if (!openTagName.length()) {
                            break;
                        }
                    }
                    if (!openTagName.length()) {
                        log.push_front("For close tag '</" + closeTagName + ">' not open tag " + QString::number(currentLine) + ", symbol " + QString::number(currentSymbol - closeTagName.length() - 3) );
                        return false;
                    }
                    level = _level;
                }
                //_closeCurrentTag удаляет крайний справа def + openTagName
                currentTagName = _closeCurrentTag(currentTagName, openTagName, def);
                level--;
                if (level == 0) {
                    childs.append(new CXmlTag(rawTag));
                    rawTag = "";
                }
            }
        }

        currentSymbol++;
    }

    if (level != 0) {
        log.push_front("Invalid xml: quantity open tags not equal quantity close tags");
        return false;
    }
    if (quoteIsOpen) {
        log.push_front("Invalid xml: You have not closed quote " + QString(lastOpenQuote) + " in xml");
        return false;
    }

    return true;
}
//TODO need test  и надо что-то придумать с   < > внутри тегов (например пишет человек про математику)
/** _trim(xml); удалить все \s символы после <  и перед > */
QString CXml::_trim(QString s) {
    //<\s+ g          => <
    s = s.replace(QRegExp("<\\s*"), "<");
    //s = s.replace(new QRegExp("<\\s*\\/\\s*"), '</');
    //<\s*\/\s*, g => </
    //<\/(\w+)\s+> => </$1>
    //s = s.replace(new QRegExp("<\\/(\\w+)\\s+>"), '</$1>');
    s = s.replace(QRegExp("\\s*>"), ">");
    return s;
}
/** */
QString CXml::_getCloseTagName(QString xml, int pos) {
    QStringList ls;
    for (int i = pos - 1; i > -1; i--) {
        ls.push_front(QString(xml[i]));
        if (xml[i] == '/') {
            break;
        }
    }
    return ls.join("");
}
/** */
QString CXml::_getOpenTagName(QString currentTagName, QString def) {
    if (currentTagName.indexOf(def) == -1) {
        return currentTagName;
    }
    QStringList ls = currentTagName.split(def);
    QString s = ls[ls.length() - 1];
    if (!s.trimmed().length() && (ls.length() - 2) > 0) {
        s = ls[ls.length() - 2];
    }
    return s;
}
/** _closeCurrentTag удаляет крайний справа def + openTagName */
QString CXml::_closeCurrentTag(QString currentTagName, QString openTagName, QString def) {
    QStringList ls = currentTagName.split(def);
    int sz = ls.length();
    int skip = sz;
    while (sz > 0) {
        QString q = ls[sz];
        if (!q.trimmed().length() || q == openTagName || q == def) {
            skip--;
        }
        if (q == openTagName) {
            break;
        }
        sz--;
    }
    QStringList result;
    for (int i = 0; i < skip; i++) {
        result.push_front(ls[i]);
    }
    return result.join(def);
}

bool CXml::_isNotPipe(QChar ch) {
    if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
        return false;
    }
    return true;
}
