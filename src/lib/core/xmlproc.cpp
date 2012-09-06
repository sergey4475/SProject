#include "xmlproc.h"
#include <QDebug>
#include <QDate>

XMLProc::XMLProc(QObject *parent) : QObject(parent)
{
}

XMLProc::~XMLProc(){

}


ItemContaner::ItemContaner(long newid, xmlItem newitem)
{
    id = newid;
    item = newitem;
}


int XMLProc::ReadXML(const QString &fname){
    QFile file( fname );
    QByteArray buf;
    QString err;
    int errLine = 0, errColumn = 0;
    if ( !file.open( QIODevice::ReadOnly ) ) return RC_ERROR;
    buf = file.readAll();
    file.close();
    xml.setContent( QString("") );
    if ( !xml.setContent( buf, false, &err, &errLine, &errColumn ) ) {
        return RC_ERROR;
    }
    init();
//CHECK_POINT
    SetModify(false);
//CHECK_POINT
    return RC_OK;
}

QString XMLProc::objClass( long id )
{
    return objClass(find(id));
}


QString XMLProc::objClass(xmlItem context)
{
    if (context.isNull()) return "";
    else return context.tagName();
}

QString XMLProc::attr(xmlItem context, const QString &name)
{
    return context.attribute(name);
}


void XMLProc::init(){
    QDomNode cur, sub;
    long id;

    //	QString s = xml.toString(4).local8Bit(); // fake call for trap troble
    if ( !xml.isDocument() ) {
        //            aLog::print(aLog::Error, tr("Bad configuration"));
        return;
    }
    //CHECK_POINT
    rootnode = xml.documentElement();
    //CHECK_POINT
    //	QDomElement root = rootnode;
    //CHECK_POINT
    cfginfo = rootnode.namedItem(md_info).toElement();
    md = rootnode.namedItem(md_metadata).toElement();
    iface = rootnode.namedItem( md_interface ).toElement();
    //actions = rootnode.namedItem( md_actions ).toElement();
    idcache.clear();
    cur = rootnode.firstChild();
    while (!cur.isNull()) {
        if ( cur.toElement().hasAttribute( mda_id ) ) {
            id = 0;
            id = attr(cur.toElement(), mda_id).toInt();
            if (id) {
                idcache.insert(id, new ItemContaner( id, cur.toElement() ) );
            }
            //			printf("cache name=%s id=%ld\n",(const char *)cur.nodeName(), id);
        }
        sub = cur.firstChild();
        if (!sub.isNull()) cur = sub;
        else
        {
            if (!cur.nextSibling().isNull()) cur = cur.nextSibling();
            else
            {
                sub = cur;
                cur.clear();
                while (cur.isNull()) {
                    sub = sub.parentNode();
                    if (sub.isNull()) break;
                    else cur = sub.nextSibling();
                }
            }
        };
    }
}

QString XMLProc::sText(xmlItem context, const QString & subname )
{
    xmlItem i;
    i = findChild( context, subname, 0 );
    if ( i.isNull() ) return ""; else return text( i );
}

xmlItem XMLProc::find(xmlItem context, const QString &name, int n)
{
    QDomNodeList l = context.elementsByTagName(name);
    return l.item(n).toElement();
}

xmlItem XMLProc::find(int id)
{
    int idl = id;
    xmlItem i;

    ItemContaner *ic;

    if (id == mdc_unknown || id == mdc_metadata) return md;
    if (id == mdc_root) return rootnode;
    if (id == mdc_info) return cfginfo;
    if (id == mdc_interface) return iface;
    if (id == mdc_actions) return actions;

    QMap<int,ItemContaner*>::const_iterator iter = idcache.find(idl);
    while (iter != idcache.end() && iter.key() == idl) {
         ic = iter.value();
         ++iter;
     }

    //ic = idcache.find(idl);
    if (ic) i = ic->item;

    return i;
}

xmlItem XMLProc::findName(xmlItem context, const QString &classname, const QString &name )
{
    xmlItem item;

    if ( !context.isNull() && !classname.isEmpty() ){
        item = firstChild( context );
        while ( !item.isNull() ) {
            if ( attr( item, mda_name ) == name ){
                break;
            }
            item = nextSibling( item );
        }
    }
    return item;
}

long XMLProc::id(xmlItem context)
{
    long i = 0;
    QString sid;

    if ( !context.isNull() ) {
        sid = attr(context, mda_id);
        if ( !sid.isEmpty() ) i=sid.toLong();
    }
    return i;
}


xmlItem XMLProc::findId(QDomElement context, const QString &classname, const QString &id)
{
    xmlItem item;

    if ( !context.isNull()){
        item = firstChild( context );
        while ( !item.isNull() ) {
            if ( attr( item, mda_id ) == id ){
                break;
            }
            item = nextSibling( item );
        }
    }
    return item;

}

xmlItem XMLProc::firstChild(xmlItem context )
{
    return context.firstChild().toElement();
}

xmlItem XMLProc::nextSibling( xmlItem context )
{
    return context.nextSibling().toElement();
}

xmlItem XMLProc::findChild(xmlItem context, const QString &classname, int n)
{
    int in = 0;
    xmlItem i = firstChild(context);
    while ( !i.isNull() ) {
        if ( classname.isEmpty() ) {
            if ( in == n ) break;
            in++;
        }
        else {
            if ( objClass( i ) == classname ) {
                if ( in == n ) break;
                in++;
            }
        }
        i = nextSibling( i );
    }
    return i;
}

int XMLProc::countChild(xmlItem context){
    int n = 0;
    xmlItem i = firstChild( context );
    while ( !i.isNull() ) {
        n++;
        i = nextSibling(i);
    }
    return n;
}

QString XMLProc::text(xmlItem context)
{
    if (context.isNull()) return "";
    return context.firstChild().nodeValue();
}

void XMLProc::setText(xmlItem context, const QString &value)
{
    QDomText t;
    if (context.isNull()) return;
    while (!context.firstChild().isNull()) {
        context.removeChild( context.firstChild() );
    }
    t = xml.createTextNode( value );
    context.appendChild( t );
    SetModify(true);
}


QByteArray XMLProc::toHex(xmlItem context){
    QString vs = text( context );
    QByteArray hex;
    return hex.append(vs).toHex();
}

int XMLProc::count(xmlItem context, const QString &classname){
    return context.elementsByTagName( classname ).count();
}


QByteArray XMLProc::fromHex(xmlItem context){
    QString vs = text( context );
    QByteArray hex = QByteArray::fromHex(vs.toAscii());
    return hex;
}

QByteArray XMLProc::toHex(QString context){
    QByteArray hex;
    return hex.append(context).toHex();
}

QByteArray XMLProc::fromHex(QString context){
    QByteArray hex = QByteArray::fromHex(context.toAscii());
    return hex;
}


void XMLProc::createNew(){
    xmlItem i;
    xml.setContent(QString("<?xml version = '1.0' encoding = 'UTF-8'?>\n"));
    //setModified( true );

    xml.appendChild( xml.implementation().createDocumentType("Конфигурация",QString::null,""));
    rootnode = xml.createElement( md_root );
    xml.appendChild( rootnode );
    rootnode = xml.documentElement();
    cfginfo = insert( rootnode, md_info, QString::null, -1 );
    iface 	= insert( rootnode, md_interface, QString::null, -1 );
    md 		= insert( rootnode, md_metadata, QString::null, -1 );
    actions	= insert( rootnode, md_actions, QString::null, -1 );
    init();
    setInfo( md_info_name, "Новая конфигурация" );
    setInfo( md_info_lastid, "0" );
    setInfo( md_info_author, "NetWorm" );
    setInfo( md_info_date, QDateTime::currentDateTime().date().toString(Qt::ISODate) );
    //setInfo( md_info_dir, "newConfig" );
    insert( md, md_globals, QString::null, -1 );
    insert( md, md_spravochniki, QString::null, -1 );
    insert( md, md_documents, QString::null, -1 );
    insert( md, md_journals, QString::null, -1 );
    i = insert( md, md_registers, QString::null, -1 );
    insert( i, md_iregisters, QString::null, -1 );
    insert( i, md_aregisters, QString::null, -1 );

    SetModify(true);
}

void XMLProc::setAttr(xmlItem context, const QString &name, const QString &value)
{
    QString v = value;
    if ( objClass( context ) == md_field && name == mda_type ) {
        if ( v.section(" ", 1).isEmpty() ) v.append(" 0 0 *");
        if ( v.section(" ", 2).isEmpty() ) v.append(" 0 *");
        if ( v.section(" ", 3).isEmpty() ) v.append(" *");
    }
    context.setAttribute( name, v );
    SetModify(true);
}

void XMLProc::setAttr(xmlItem context, const QString &name, int value)
{
    context.setAttribute(name, value);
    SetModify(true);
}

QString XMLProc::info(const QString &name)
{
    return text(cfginfo.namedItem( name ).toElement()); //.firstChild().nodeValue();
}

void XMLProc::setInfo(const QString &name, const QString &value)
{
    xmlItem i;
    i = cfginfo.namedItem( name ).toElement();
    if (i.isNull()) {
        i = xml.createElement( name );
        cfginfo.appendChild( i );
    }
    setText(i, value);
    SetModify(true);
}


long XMLProc::nextID()
{
    long id = 0;
    id = info( md_info_lastid ).toLong();
    if (id == 0 ) id = context_startid;
    ++id;
    setInfo( md_info_lastid, QString("%1").arg(id) );
    return id;
}


xmlItem XMLProc::insert(xmlItem context, const QString &otype, const QString &name, long id)
{
    xmlItem i;

    if ( id==0 ) id = nextID();
    i = xml.createElement( otype );
    if ( id >= 100 ) setAttr(i, mda_id, id );
    if ( !name.isNull()) setAttr(i, mda_name, name );
    context.appendChild(i);
    if ( id > 0 ) idcache.insert(id, new ItemContaner(id,i) );
    SetModify(true);
    return i;
}

void XMLProc::remove(xmlItem context)
{
    long id;
    xmlItem child;

    QDomNode own = context.parentNode();
    if (!own.isNull()) {
        id = attr( context, mda_id ).toLong();
        child = firstChild(context);
        remove(child);
        idcache.remove( id );
        own.removeChild(context);
        SetModify(true);
    }
}


int XMLProc::write(const QString &fname)
{
    return write(xml, fname);
}
int XMLProc::write(QDomDocument doc, const QString &fname)
{
    QFile file( fname );
    QByteArray buf(xml.toString(4).toUtf8());
    if ( file.open( QIODevice::WriteOnly ) ) {
    QTextStream ts( &file );
    doc.save(ts, 4);
    file.close();
    return RC_OK;
    }
    return RC_ERROR;
}

bool XMLProc::GetModify()
{
    return modify;
}

void XMLProc::SetModify(bool mode )
{
    modify = mode;
}

