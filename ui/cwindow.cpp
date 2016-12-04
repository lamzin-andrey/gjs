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
    CWebPage *page = new CWebPage(wv);
    wv->setPage(page);
    wv->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    wv->page()->settings()->setAttribute(QWebSettings::AutoLoadImages,   true);
    wv->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);

    /*wv->page()->settings()->setAttribute(QWebSettings::JavascriptCanCloseWindows, true);
    wv->page()->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    wv->page()->settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);*/



    this->setCentralWidget(wv);
    this->addObject(this, "Qt");
    php = new CPhpInterface(this, wv);
    os  = new OS(this, wv);

    this->addObject(php, "PHP");
    this->addObject(os, "OS");

    QString js = lib.readtextfile(QApplication::applicationDirPath() + "/default/tools/js/j.js");
    this->js(js);

    workdir = appDir;
    cXml = new CXml(appDir + "/index.html");
    this->_setMainMenu();
    getURL(os->getLocalFileStartUrl() + "/" + appDir + "/index.html", false);

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
QString CWindow::openFileDialog(QString caption, QString dir, QString filter) {
    return QFileDialog::getOpenFileName(this, caption, dir, filter);
}
QString CWindow::saveFileDialog(QString caption, QString dir, QString filter) {
    return QFileDialog::getSaveFileName(this, caption, dir, filter);
}

QString CWindow::openDirectoryDialog(QString caption, QString dir) {
    return  QFileDialog::getExistingDirectory(this, caption, dir);
}

void CWindow::moveTo(int x, int y) {
    QRect r = this->geometry();
    int w = r.width();
    int h = r.height();
    r.setX(x);
    r.setY(y);
    r.setWidth(w);
    r.setHeight(h);
    this->setGeometry(r);
}
void CWindow::resizeTo(int x, int y) {
    QRect r = this->geometry();
    r.setWidth(x);
    r.setHeight(y);
    this->setGeometry(r);
}
void CWindow::quit() {
    QApplication::quit();
}

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
/**
 *
*/
void CWindow::_setMainMenu() {
    bool hasMainMenu = false;
    QList<CXml*> list = cXml->getElementsByTagName("html");
    if (list.length() > 0) {
        list = list[0]->getElementsByTagName("head");
        if (list.length() > 0) {
            list = list[0]->getElementsByTagName("menubar");
            if (list.length() > 0) {
                list = list[0]->getElementsByTagName("menu");
                if (list.length() > 0) {
                    hasMainMenu = true;
                }
            }
        }
    }
    if (!hasMainMenu) {
        return;
    }
    //return;
    menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    for (int i = 0; i < list.length(); i++) {
        QMenu* tempMainMenu =  menubar->addMenu(list[i]->getAttribute("title"));
        this->_setMenuItems(tempMainMenu, list[i]->childs);
    }
    return; //TODO remove me and bottom

    menubar = new QMenuBar(this);
    this->setMenuBar(menubar);

    QStringList mainList, actionList1, actionList2;
    mainList << "File" << "Edit" << "Build";
    actionList1 << "Open" << "Save" << "SaveAs";
    actionList2 << "Undo" << "Redo" << "CopyFromBuffer";

    for (int i = 0; i < 3; i++) {
        QMenu* tempMainMenu =  menubar->addMenu(mainList[i]);
        QStringList temp;
        if (i == 0) {
            temp = actionList1;
        }
        if (i == 1) {
            temp = actionList2;
        }
        if (i == 3) {
            temp.clear();
            //tempMainMenu->addSeparator()
            //tempMainMenu->addMenu()
        }
        for (int j = 0; j < temp.length(); j++) {
            QAction* act = tempMainMenu->addAction(temp[j]);
            QString tempJsAction = "on" + temp[j];
            CAction* cact = new CAction(temp[j], tempJsAction);
            connect(act, SIGNAL(triggered()), cact, SLOT(triggered()));
            connect(cact, SIGNAL(triggeredExt(QString, QString)), this, SLOT(onMainMenuAction(QString, QString)));
        }
    }

}

void CWindow::onMainMenuAction(QString title, QString action) {
    action = action.replace("(", "");
    action = action.replace(")", "");
    this->js(action + "()");
}

void CWindow::_setMenuItems(QMenu* menu, QList<CXml*> items)  {
    for (int i = 0; i < items.length(); i++) {
        if (items[i]->tagName.toUpper() == "ITEM") {
            QAction* act = menu->addAction(items[i]->innerXML);
            QString jsAction = items[i]->getAttribute("onselect");
            CAction* cact = new CAction(items[i]->innerXML, jsAction );
            connect(act, SIGNAL(triggered()), cact, SLOT(triggered()));
            connect(cact, SIGNAL(triggeredExt(QString, QString)), this, SLOT(onMainMenuAction(QString, QString)));
        }
        if (items[i]->tagName.toUpper() == "SEPARATOR") {
            menu->addSeparator();
        }
        if (items[i]->tagName.toUpper() == "MENU") {
            QMenu* nextMenu = menu->addMenu(items[i]->getAttribute("title"));
            _setMenuItems(nextMenu, items[i]->childs);
        }
    }
}

QString CWindow::readFileAsBinaryString(QString filename) {
    QString r = "";
    QStringList list;
    if (QFile::exists(filename)) {
        QFileInfo info;
        info.setFile(filename);
        unsigned long size = (unsigned long)info.size();
        char cFilename[filename.length()];
        for (int i = 0; i < filename.length(); i++) {
            cFilename[i] = filename.at(i).toLatin1();
        }
        BinFile file(cFilename);
        for (long i = 0; i < size; i++) {
            short byte;
            file.readByte(i, byte);
            list << QString::number(byte);
        }
        r = list.join(',');
        return r;
    }
    return r;
}


int CWindow::writefile(QString fileName, QString data)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QByteArray by = data.toLatin1();
    file.write(by);
    unsigned long sz = file.size();
    file.close();
    return sz;
}
