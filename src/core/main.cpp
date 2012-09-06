#include <QApplication>
#include <QTextCodec>
#include <QDir>
#include <QDebug>
#include <QLibrary>
#include "interface.h"
#include <iisTaskPanel>
#include "scripts.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);

    a.addLibraryPath(QApplication::applicationDirPath()+"/lib");
    a.addLibraryPath(QApplication::applicationDirPath()+"/plugins");


    XMLProc *xml = new XMLProc();
    xml->ReadXML(QApplication::applicationDirPath()+"/ifase_.xml");

    sEngine *Engine = new sEngine(xml);

    interface *iface = new interface(xml->find(mdc_root),Engine);
    iface->show();

    Engine->on_systemstart();

    return a.exec();
}
