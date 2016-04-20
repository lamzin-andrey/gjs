#include "cwindow.h"

CWindow::CWindow(QString appDir, CMetadata metadata, QWidget *parent):QMainWindow(parent)
{
    this->metadata = metadata;
    Qt::WindowFlags flags = 0;
    if (metadata.max && metadata.min && metadata.close && !metadata.question) {
        ;
    } else {
        if (metadata.max) {
            flags = flags | Qt::WindowMaximizeButtonHint;
        }
        if (metadata.min) {
            flags = flags | Qt::WindowMinimizeButtonHint;
        }
        if (metadata.close) {
            flags = flags | Qt::WindowCloseButtonHint;
        }
        if (metadata.question) {
            flags = flags | Qt::WindowContextHelpButtonHint;
        }
    }
    if (metadata.onlyTop) {
        flags = flags | Qt::WindowStaysOnTopHint;
    }
    if (metadata.noFrame) {
        flags = flags | Qt::SplashScreen;
    }
    if (metadata.fullScreen) {
        //TODO посмотреть, как делал в локере flags = flags | Qt::Window;
    }
    this->setWindowFlags(flags);
    lib.parentMBoxWidget = this;
    //setWindowTitle(metadata.sTitle + ", w = " + QString::number(metadata.windowWidth)  + ", h = " + QString::number(metadata.windowHeight));
    setWindowTitle(metadata.sTitle);

    resized = false;
    if (metadata.windowWidth != -1 || metadata.windowHeight != -1) {
        timer = new QTimer();
        timer->setInterval(1);
        connect(
                    timer, SIGNAL(timeout()),
                    this, SLOT(onTimer()) );
        timer->start();
    } else {
        this->show();
    }


    loading = false;
    lastUrl = "";
    wv = new CWebView();
    wv->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    wv->page()->settings()->setAttribute(QWebSettings::AutoLoadImages,   false);
    wv->page()->settings()->setAttribute(QWebSettings::PluginsEnabled,false);



    this->setCentralWidget(wv);
    this->addObject(this, "Qt");
    php = new CPhpInterface(this, wv);
    this->addObject(php, "PHP");

    QString js = lib.readtextfile(QApplication::applicationDirPath() + "/default/tools/js/j.js");
    this->js(js);

    workdir = appDir;
    getURL("file://" + appDir + "/index.html", false);

}

CWindow::~CWindow()
{
    wv->~QWebView();
}

void CWindow::loadImages(bool flag)
{
    wv->page()->settings()->setAttribute(QWebSettings::AutoLoadImages, flag);
}

void CWindow::stop()
{
    wv->stop();
    loading = false;
}

QString CWindow::currentText()
{
    return wv->page()->currentFrame()->toPlainText();
}

QString CWindow::currentHtml()
{
    return wv->page()->currentFrame()->toHtml();
}

void CWindow::addObject(QObject* object, QString jsName)
{
    wv->page()->currentFrame()->addToJavaScriptWindowObject(jsName, object);
}

void CWindow::js(QString script)
{
    wv->page()->currentFrame()->evaluateJavaScript(script);
}

void CWindow::setHtml(QString s)
{
    wv->page()->currentFrame()->setHtml(s);
}

void CWindow::onLoad(bool success)
{
    if (success)
    {
        //TODO если не поможет после создания, добавить тут
        loading = false;
        QString s = wv->page()->currentFrame()->toHtml();
        QString path = QApplication::applicationDirPath();
        if (writeresult)lib.writetextfile(path + "/data/cache/last.html", s);
        this->html = s;
        emit(loadComplete());
    }
    else
    {
        if (lastUrl == "") {loading = true; return;}
        //lib.qMessageBox("Test", "Can't load " + lastUrl + " try count = " + QString::number(counttry));
        counttry++;
        wv->stop();
        if (counttry > 0)
        {
            loading = false;
            emit(errorConnect("Не удалось закачать " + lastUrl + " проверьте соединение с Интернетом."));
            return;
        }

        lib.qMessageBox("After stop", "Can't load " + lastUrl + " try count = " + QString::number(counttry));

        disconnect(wv, SIGNAL(loadFinished(bool)), this, SLOT(onLoad(bool)));
        connect(wv, SIGNAL(loadFinished(bool)), this, SLOT(onLoad(bool)));
        wv->load(QUrl(lastUrl));
    }
}

void CWindow::getURL(QString url, bool writeresult)
{
  if (!loading)
  {
      wv->stop();
      counttry = 0;
      lastUrl  = url;
      loading  = true;
      connect(wv, SIGNAL(loadFinished(bool)), this, SLOT(onLoad(bool)));
      wv->load(QUrl(url));
      this->html = "";
      this->writeresult = writeresult;
  }
}

void CWindow::fixSize()
{
    this->setMaximumSize(this->geometry().width(), this->geometry().height());
    this->setMinimumSize(this->geometry().width(), this->geometry().height());
}
//========================================================================
//========================PUBLIC JS SLOTS=================================
QString CWindow::appDir() {
    return workdir;
}

QString CWindow::getLineDelimeter() {
    return CMetadata::PIPE;
}

void CWindow::setLineDelimeter(QString  pipe) {
    CMetadata::PIPE = pipe;
}


void CWindow::onTimer(QPrivateSignal s) {
    if (resized == false) {
        resized = true;
        QRect rect = this->geometry();
        //QPoint pos = this->pos();

        int x = 0;
        int y = 0;
        int w = 600;
        int h = 400;



        if (metadata.windowWidth != -1 && metadata.windowWidth > 0) {
            w = metadata.windowWidth;
        }
        if (metadata.windowHeight != -1 && metadata.windowHeight > 0) {
            h = metadata.windowHeight;

        }
        x = round((QApplication::desktop()->screenGeometry().width() - w) / 2);
        y = round((QApplication::desktop()->screenGeometry().height() - h) / 2);
        /*QScreen *scr = new QScreen();
        qDebug() << scr.availableSize().width();*/

        rect.setX(x);
        rect.setY(y);
        rect.setWidth(w);
        rect.setHeight(h);
        this->setGeometry(rect);
        if (metadata.fixedSize && metadata.windowWidth != -1 && metadata.windowWidth > 0) {
            this->setMaximumWidth(w);
        }
        if (metadata.fixedSize && metadata.windowHeight != -1 && metadata.windowHeight > 0) {
            this->setMaximumHeight(h);
        }
        this->show();
    }
}
