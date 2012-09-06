#include "smetaobject.h"

int sMetaObject::v_lastId = 101;

sMetaObject::sMetaObject(const QString &objectclass,
                         const QString &objectname,
                         sMetaObject *parent)
    :QObject(parent)
{
    setObjectName( objectname );
    setClassName( objectclass );
}

sMetaObject::~sMetaObject(){}

qint64 sMetaObject::id()
{
    return v_id;
}

void sMetaObject::setId(qint64 new_id){
    v_id = new_id;
}


void sMetaObject::setClassName( const QString &name )
{
    v_className = name;
}

QString sMetaObject::className(){
    return v_className;
}

QString sMetaObject::name(){
    return objectName();
}

sMetaObject * sMetaObject::rootObject(){
    sMetaObject *o = parentMetaObject();
    while ( o->parentMetaObject() ) o = o->parentMetaObject();
    if ( !o->inherits("AMetaData" ) ) o = 0;
    return o;
}

sMetaObject * sMetaObject::parentMetaObject()
{
    sMetaObject *p = (sMetaObject *) parent();
    if ( !p ) p = v_parent;
    else if ( !p->inherits("sMetaObject") ) p = 0;
    return p;
}

void sMetaObject::setParentMetaObject( sMetaObject * parent )
{
    v_parent = parent;
}

QString sMetaObject::description()
{
    return v_description;
}

void sMetaObject::setDescription( const QString &descr )
{
    v_description = descr;
}

void sMetaObject::setAttr( const QString &name, const QVariant &value )
{
    if ( value.isNull() && attrExists( name ) ) v_attr.remove( name );
    else v_attr[ name ] = value;
}

QVariant
sMetaObject::attr( const QString &name ) const
{
    return v_attr.value( name, QVariant() );
}

QVariant sMetaObject::attr( int idx ) const
{
    return attr( attrName( idx ) );
}

QString sMetaObject::attrName( int idx ) const
{
    if ( idx < 0 || idx >= attrCount() ) return QString::null;
    return v_attr.keys().at( idx );
}

bool sMetaObject::attrExists( const QString &name )
{
    return v_attr.contains( name );
}

int sMetaObject::attrCount() const
{
    return v_attr.size();
}

int sMetaObject::lastId()
{
    static QMutex m;

    m.lock();
    int res = v_lastId;
    v_lastId++;
    m.unlock();
    return res;
}

void sMetaObject::setLastId( int id )
{
    v_lastId = id;
}

int sMetaObject::childCount()
{
    return v_child.count();
}

sMetaObject * sMetaObject::child( int idx )
{
    if ( idx < 0 || idx >= childCount() ) return 0;
    return v_child.values().at( idx );
}

sMetaObject * sMetaObject::child( const QString &name )
{
    return v_child.value( name, 0 );
}

void sMetaObject::addChild( sMetaObject * c )
{
    QString name;

    if ( c ) {
        name = c->name();
        if ( name.isEmpty() ) name = c->className();
        v_child.insertMulti( name, c );
    }
}

void sMetaObject::removeChild( sMetaObject * c )
{
    if ( c ) v_child.remove( v_child.key( c ) );
}

QString sMetaObject::varToStr( QVariant v )
{
    QString s;

    switch (v.type()){
      case QVariant::ByteArray:
        s = v.toByteArray().toHex();
        break;
      default:
        s = v.toString();
    }
    return s;
}

QVariant sMetaObject::strToVar(const QString &str, QVariant::Type t)
{
    QVariant v;

    switch (t){
      case QVariant::ByteArray:
        v = QByteArray::fromHex(str.toLatin1());
        break;
      default:
        v = str;
    }
    if ( v.convert( t ) ) return v;
    return QVariant();
}




