#include "scripts.h"

sEngine::sEngine(XMLProc *xml)
{
    code = new QScriptEngine();
    md = xml;
    next_obj_id = 1;
    mGlobal = md->sText( md->find( md->find( mdc_metadata ), md_globals, 0 ), md_sourcecode );
    QScriptValue system = code->newQObject(this);
    code->evaluate(mGlobal);
    code->globalObject().setProperty("sys",system);
}

sEngine::~sEngine(){
    values.clear();
}

void sEngine::on_systemstart(){
    code->globalObject().property("on_systemstart").call();
}

void sEngine::Message(int n, const QString &msg)
{
    qDebug() << msg;
}

QString sEngine::Time() {
    return QTime::currentTime().toString("hh:mm:ss");
}

QString sEngine::Date() {
    return QDate::currentDate().toString("dd.MM.yy");
}

void sEngine::ExitApp() {
    qApp->quit();
}

QWidget* sEngine::OpenForm(xmlItem item)//Q_ULLONG ido)
{
    QString description, sourcecode, defaultmod, dialogform;

//    md->find(md->find(md->find( mdc_metadata ),md_form, 0 ),);

    dialogform  = md->sText(item, md_formdesign);
    description = md->sText(item, md_description);
    sourcecode  = md->sText(item, md_sourcecode);
    defaultmod  = md->sText(item, md_defaultmod);

    QByteArray buf = md->fromHex(dialogform);
    QBuffer b(&buf);
    b.open(QIODevice::ReadOnly );

    QWidget *form = UI.load(&b);
    b.close();

    return form;
}
