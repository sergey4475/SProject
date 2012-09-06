#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainform.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("cp1251");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);


    QApplication a(argc, argv);
    mainForm w;
    w.show();
    
    return a.exec();
}
