#include "cmetadata.h"

CMetadata::CMetadata(QString file)
{
    file = file + "/index.html";
    QString s = lib.readtextfile(file, true);
    QStringList arr = s.split('\n');

    QStringList aHead;
    int headComplete = 0;

    QStringList aMenu;
    int menuComplete = 0;

    QStringList aTitle;
    int titleComplete = 0;

    QStringList aMeta;

    for (int i = 0; i < arr.length(); i++) {
        s = arr[i];
        if (s.indexOf("<head") != -1) {
            headComplete = 1;
        }
        if (headComplete == 1) {
            aHead.append(arr[i]);
        }
        if (s.indexOf("</head>") != -1) {
            headComplete = 2;
        }

        if (s.indexOf("<menu") != -1) {
            menuComplete = 1;
        }
        if (menuComplete == 1) {
            aMenu.append(arr[i]);
        }
        if (s.indexOf("</menu>") != -1) {
            menuComplete = 2;
            break;
        }

        if (s.indexOf("<title") != -1) {
            titleComplete = 1;
        }
        if (titleComplete == 1) {
            aTitle.append(arr[i]);
        }
        if (s.indexOf("</title>") != -1) {
            titleComplete = 2;
        }

        if (s.indexOf("<meta") != -1) {
            aMeta.append(arr[i]);
        }
    }
    _setTitle(aTitle);
    _setWinButtons(aMeta);
}

void CMetadata::_setWinButtons(QStringList aMeta) {
    title = "";
    for (int i = 0; i < aMeta.length(); i++) {
        QString s = aMeta[i];
        QString mark = "windowButtons";
        int n = s.indexOf(mark);
        if (n != -1) {
            mark = "content";
            n = s.indexOf(mark);
            int qq = 0;
            QString mask = "";
            if (n != -1) {
                for (int j = n + mark.length(); j < s.length(); j++) {
                    QChar ch = s[j];
                    if (ch == '"' || ch == '\'') {
                        qq++;
                        continue;
                    }
                    if (qq == 1) {
                        mask += ch;
                    }
                    if (qq == 2) {
                        break;
                    }
                }
                if (qq == 2 && mask.length() == 4) {
                    min      = (mask[0] == '1');
                    max      = (mask[1] == '1');
                    close    = (mask[2] == '1');
                    question = (mask[3] == '1');
                }
            }

            if (s.indexOf("onlyTop") != -1) {
                onlyTop = true;
            }
            if (s.indexOf("noFrame") != -1) {
                noFrame = true;
            }
            if (s.indexOf("fullScreen") != -1) {
                fullScreen = true;
            }
            break;
        }
    }
}
void CMetadata::_setTitle(QStringList aTitle) {
    QString s = aTitle.join('\n');
    int st = s.indexOf("<title");
    st = s.indexOf(">", st);
    int end = s.indexOf("</title", st);
    if (st < end && end) {
        s = s.mid(st + 1, end - st - 1);
        title = s.trimmed();
    }
}
