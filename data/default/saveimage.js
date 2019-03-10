function e(i) {return document.getElementById(i);}


function doLog(s) {
	e('doCout').innerHTML += (e('doCout').innerHTML + '<div style="color:blue">' + s + '</div>');
}

function initDoImage() {
	doLog('start');
	//e('doPreview').
	e('doLoadImage').addEventListener('change', doOnSelectImage, true);
	e('doLoadImage').addEventListener('load', doOnLoadFile, true);
}
/**
 *  
*/
function doOnSelectImage() {
	doLog('onselect handler');
	window.doFileReader = new FileReader();
	doFileReader.onloadend = doOnLoadFile;
	doFileReader.readAsDataURL(e('doLoadImage').files[0]);
}

function doOnLoadFile(evt) {
	doLog('OnLoadFile handler');
	var s = doFileReader.result;
	e('doPreview').src = s;
	doLog(s);
}
/*
 * QT C++ code
 * 
 * #include <QtCore>
#include <QApplication>

#include <QImage>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>
#include <QLabel>

int main(int argc, char *argv[]) {
    QString filename = "output.png";
    if (argc > 1) {
        filename = argv[1];
    }
    QApplication a(argc, argv);
    QTextStream stream(stdin);
    qDebug() << "reading";
    //stream.readAll();
    qDebug() << "read complete";
    QByteArray base64Data = stream.readAll().toAscii();
    QImage image;
    qDebug() << base64Data;
    image.loadFromData(QByteArray::fromBase64(base64Data), "PNG");
    QLabel label(0);
    label.setPixmap(QPixmap::fromImage(image));
    label.show();
    qDebug() << "writing";
    image.save(filename, "PNG");
    qDebug() << "write complete";
    return a.exec();
}
 * */
