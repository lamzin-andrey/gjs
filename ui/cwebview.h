#ifndef CWEBVIEW_H
#define CWEBVIEW_H

#include <QtWebKitWidgets/QWebView>
#include <QContextMenuEvent>

class CWebView : public QWebView
{
    Q_OBJECT
public:
    explicit CWebView(QWidget *parent = 0);
protected:
    void contextMenuEvent(QContextMenuEvent *);
signals:
    
public slots:
    
};

#endif // CWEBVIEW_H
