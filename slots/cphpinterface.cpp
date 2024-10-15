#include "cphpinterface.h"

CPhpInterface::CPhpInterface(QWidget *parent, CWebView *webView) :
    QWidget(parent)
{
    procIsInit = false;
    this->webView = webView;
    cprocId = 0;

    for (unsigned int i = 0; i < 255; i++) {
        fileHandlerState[i] = 0;
    }

    qDirIteratorLastPath = "";
    qDirIteratorIsInit = false;
}

int CPhpInterface::file_put_contents(QString path, QString data, int flag) {
    bool append = (flag == 1 || flag == 8);
    return lib.writetextfile(path, data, append);
}

bool CPhpInterface::file_exists(QString path) {
    return QFile::exists(path);
}

bool CPhpInterface::is_dir(QString path) {
    QFileInfo info;
    info.setFile(path);
    return info.isDir();
}

qint64  CPhpInterface::filesize(QString path) {
    Utils lib;
    if (this->is_dir(path)) {
        QString folders = this->_scandir(path);
        QStringList ls = folders.split(CMetadata::PIPE);
        qint64 sz = 0;
        for (int i = 0; i < ls.size(); i++) {
            QString currPath = ls[i];
            QString shortname = ls[i].replace(path + "/", "");
            if (shortname != "." && shortname != "..") {
                sz += this->filesize(currPath);
            }
        }
        return sz;
    }
    QFileInfo info;
    info.setFile(path);
    return info.size();
}

QString CPhpInterface::_scandir(QString path) {
    QDirIterator it(path, QDirIterator::NoIteratorFlags);
    QStringList ls;
    while (it.hasNext()) {
        ls.append(it.next() );
    }
    return ls.join(CMetadata::PIPE);
}

QStringList CPhpInterface::partDir(QString path, unsigned int sz, bool reset) {
    //QDirIterator it(path, QDirIterator::NoIteratorFlags);

    if (reset || qDirIteratorLastPath != path || !this->qDirIteratorIsInit) {
        if (this->qDirIteratorIsInit) {
            this->qDirIterator->~QDirIterator();
        }
        this->qDirIterator = new QDirIterator(path, QDirIterator::NoIteratorFlags);
        qDirIteratorLastPath = path;
        this->qDirIteratorIsInit = true;
    }

    QStringList ls;
    unsigned int i = 0;
    while (this->qDirIterator->hasNext()) {
        QStringList aItem;
        QString item = "";
        this->qDirIterator->next();
        QFileInfo fi = this->qDirIterator->fileInfo();
        // size/mtime/owner/grp/TEname/path
        // T - type, E - isExec
        item = QString::number(fi.size(), 16);
        aItem.push_back(item);
        item = QString::number(fi.lastModified().toTime_t(), 16);
        aItem.push_back(item);
        aItem.push_back(fi.owner());
        item = fi.group();
        if (item == fi.owner()) {
            aItem.push_back("");
        } else {
            aItem.push_back(item);
        }
        /*
         * 0 - dir
         * 1 - file
         * 2 - symlink dir
         * 3 - symlink file
         *
        */
        if (fi.isSymLink()) {
            item = "3";
            if (fi.isDir()) {
                item = "2";
            }
        } else {
            item = "1";
            if (fi.isDir()) {
                item = "0";
            }
        }

        /*
         * 0 - no exec
         * 1 - exec
        */
        if (fi.isExecutable() && !fi.isDir()) {
            item += "1";
        } else {
            item += "0";
        }
        item += fi.fileName();
        aItem.push_back(item);
        item = fi.filePath();
        aItem.push_back(item);
        item = aItem.join(QString('/'));
        ls.append(item);
        // ls.append(this->qDirIterator->next().replace(path + "/", "") );
        i++;
        if (i >= sz) {
            break;
        }
    }
    if (!this->qDirIterator->hasNext()) {
        ls.append("EOF");
    }
    return ls;
}


QString CPhpInterface::file_get_contents(QString path) {
    return lib.readtextfile(path, true);
}
unsigned int CPhpInterface::exec(QString command, QString onFinish, QString onOutput, QString onError) {
    return this->execCProcess(command, onFinish, onOutput, onError);
}

unsigned int CPhpInterface::execCProcess(QString command, QString onFinish, QString onOutput, QString onError) {
    cprocId++;
    CProcess * proc = new CProcess(cprocId, onOutput, onError, onFinish, this);
    connect(proc, SIGNAL(onOutputSg(QString, unsigned int)),
                  this, SLOT(onCProcessOutput(QString , unsigned int )));
    connect(proc,
            SIGNAL(
                onErrorSg(QString, unsigned int)),
            this, SLOT(
                onCProcessErrorOutput(QString, unsigned int))
           );
    connect(proc, SIGNAL(onEmptyArgumentsSg()),
            this, SLOT(onCProcessEmptyArguments()));

    connect(proc, SIGNAL(onEmptyOutputSg(bool)),
            this, SLOT(onCProcessEmptyOutput(bool)) );

    connect(proc, SIGNAL(onFinishSg(QString, unsigned int)),
            this, SLOT(onCProcessFinish(QString, unsigned int)) );

    proc->exec(command);
    cprocList.append(proc);
    return cprocId;
}

void CPhpInterface::onCProcessOutput(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessOutput!");
        this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(evaluateJavaScript);
}

void CPhpInterface::onCProcessErrorOutput(QString onErrorOutputEvaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessERROutput!");
    this->webView->page()
                ->currentFrame()
                ->evaluateJavaScript(onErrorOutputEvaluateJavaScript);
}

void CPhpInterface::onCProcessEmptyArguments() {
    this->webView->page()->currentFrame()->evaluateJavaScript("alert('OnEmptyArgs')");
}

void CPhpInterface::onCProcessEmptyOutput(bool isErrorOutput) {
    QString s = "alert('OnEmptyOut')";
    if (isErrorOutput) {
        s = "alert('OnEmptyErrOut')";
    }
    this->webView->page()->currentFrame()->evaluateJavaScript(s);
}
void CPhpInterface::onCProcessFinish(QString evaluateJavaScript, unsigned int resId) {
    //lib.qMessageBox("CPhp", "onCProcessFinish(" + evaluateJavaScript + ")");
    this->webView->page()->currentFrame()->evaluateJavaScript(evaluateJavaScript);
}
bool CPhpInterface::isRun(unsigned int n) {
    for (unsigned int i = 0; i < cprocList.length(); i++)  {
        if (cprocList[i]->id() == n) {
            return cprocList[i]->isRun();
        }
    }
    return false;
}
unsigned int CPhpInterface::getSysId(unsigned int n) {
    for (unsigned int i = 0; i < cprocList.length(); i++)  {
        if (cprocList[i]->id() == n) {
            return cprocList[i]->systemId();
        }
    }
    return 0;
}

bool CPhpInterface::unlink(QString path) {
    bool r = this->file_exists(path);
    if (r){
        return QFile::remove(path);
    }
    return r;
}

bool CPhpInterface::mkdir(QString path) {
    QDir dir;
    return dir.mkpath(path);
}


int CPhpInterface::open(QString filename, QString mode) {
    bool success = false;
    unsigned int idx = 0;
    FILE *fh = this->getFreeFile(filename, mode, success, idx);
    if (!success) {
        return -1;
    }


    return idx;
}

bool CPhpInterface::close(unsigned int fileId) {
    if (1 != fileHandlerState[fileId]) {
        return false;
    }
    int n = fclose(fileHandlersList.at(fileId));
    fileHandlerState[fileId] = 0;

    return (n == 0);
}

QString CPhpInterface::gets(unsigned int fileId) {
    if (1 != fileHandlerState[fileId]) {
        return "1!=";
    }
    unsigned int sz = 4096;
    char cStr[sz];
    fgets(cStr, sz - 2, fileHandlersList.at(fileId));
    string str(cStr);

    return QString::fromStdString(str);
}


bool CPhpInterface::eof(unsigned int fileId) {
    if (1 != fileHandlerState[fileId]) {
        return true;
    }


    return feof(fileHandlersList.at(fileId));
}

bool CPhpInterface::puts(unsigned int fileId, QString s) {
    if (1 != fileHandlerState[fileId]) {
        return false;
    }

    fputs(s.toStdString().c_str(), fileHandlersList.at(fileId));

    return true;
}

FILE *CPhpInterface::getFreeFile(QString filename, QString mode, bool &success, unsigned int &idx) {
    for (unsigned int i = 0; i < 255; i++) {
        if (fileHandlerState[i] == 1) {
            continue;
        }
        idx = i;
        success = true;

        FILE* fh = fopen(filename.toStdString().c_str(), mode.toStdString().c_str());
        fileHandlersList.insert(idx, fh);
        fileHandlerState[idx] = 1;

        return fh;
    }

    return NULL;
}

void CPhpInterface::replaceInFile(QString filename, QString search, QString replace, QString outfile) {
    //QString s = file_get_contents(filename);

    FILE* fh = fopen(filename.toStdString().c_str(), "r");
    string r = "";

    unsigned int sz = 4096;
    while (!feof(fh)) {
        char cStr[sz];
        fgets(cStr, sz - 2, fh);
        string str(cStr);
        r += str;
    }
    fclose(fh);
    int idx = libStd.pos(search.toStdString(), r);
    if (idx != -1) {
        r = libStd.Delete(r, idx, search.length());
        r = libStd.Insert(r, replace.toStdString(), idx);
    }


    FILE* fh2 = fopen(outfile.toStdString().c_str(), "w");
    fputs(r.c_str(), fh2);
    fclose(fh2);
}


// hashes
QString CPhpInterface::md5(QString s) {
    string ss = s.toStdString();
    int size = ss.length();
    QByteArray ba = QByteArray::fromRawData(ss.c_str(), size);
    ba = QCryptographicHash::hash(ba, QCryptographicHash::Md5);
    QString r(ba.toHex());
    return r;
}


QString CPhpInterface::md5_file(QString filename)
{
    QFile f(filename);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(QCryptographicHash::Md5);
        QByteArray ba = f.readAll();
        //QByteArray ba2 = *ba;
        f.close();
        hash.addData(ba);
        QString r = QString(hash.result().toHex());
        return r;

    }

    return "";
}
