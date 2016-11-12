#ifndef CWEBPAGE_H
#define CWEBPAGE_H

#include <QWebPage>
#include "../lib/utils.h"
#include "../slots/os.h"

class CWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit CWebPage(QWidget *parent = 0);
    bool shouldInterruptJavaScript();
protected:
    void javaScriptConsoleMessage( const QString & message, int lineNumber, const QString & sourceID );

private:
    Utils lib;
signals:
    
public slots:
    
};

#endif // CWEBPAGE_H
