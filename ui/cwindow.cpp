#include "cwindow.h"

CWindow::CWindow(QString appDir, CMetadata metadata, QWidget *parent):QMainWindow(parent)
{
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
    this->setWindowTitle(metadata.title);


    loading = false;
    lastUrl = "";
    wv = new CWebView();
    wv->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    wv->page()->settings()->setAttribute(QWebSettings::AutoLoadImages,   false);
    wv->page()->settings()->setAttribute(QWebSettings::PluginsEnabled,false);
    this->setCentralWidget(wv);
    this->addObject(this, "Qt");
    php = new CPhpInterface(this);
    this->addObject(php, "PHP");
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
