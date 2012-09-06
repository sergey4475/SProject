#ifndef SMETAOBJECT_H
#define SMETAOBJECT_H

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QMutex>

class sMetaObject : public QObject
{
    Q_OBJECT
public:
    explicit sMetaObject(const QString &objectclass  = QString::null,
                         const QString &objectname = QString::null,
                         sMetaObject *parent = 0);
    ~sMetaObject();
    void setClassName(const QString &name);

    qint64 id();
    void setId( qint64 new_id);
    QString className();
    QString name();
    sMetaObject *rootObject();
    sMetaObject *parentMetaObject();
    void setParentMetaObject( sMetaObject * parent );

    QString description();
    void setDescription( const QString &descr );

    void setAttr( const QString &name, const QVariant &value );
    QVariant attr( const QString &name ) const;
    QVariant attr( int idx ) const;
    QString attrName( int idx ) const;
    bool attrExists( const QString &name );
    int attrCount() const;

    static int lastId();
    static void setLastId( int id );
    static QString  varToStr( QVariant v );
    static QVariant strToVar( const QString &str, QVariant::Type t );


    int childCount();
    sMetaObject * child( int idx );
    sMetaObject * child( const QString &name );
    void addChild( sMetaObject * c );
    void removeChild( sMetaObject * c );

signals:
    
public slots:

private:
    static int v_lastId;
    sMetaObject *v_parent;
    qint64 v_id;
    QString v_className;
    QString v_description;
    QMap <QString, QVariant> v_attr;
    QMap <QString, sMetaObject *> v_child;
};

class sMetaGroup: public sMetaObject
{
Q_OBJECT
public:
    sMetaGroup( const QString &groupname, sMetaObject *parent = 0 )
        :sMetaObject( groupname, QString::null, parent ){
    }
};

template<class T>
class  sMetaGroupA : public sMetaGroup
{
//    Q_OBJECT
public:

    sMetaGroupA( sMetaObject * parent = 0 )
    :sMetaGroup( "", parent )
    {
    }
};

typedef sMetaGroupA<sMetaObject> sMetaGroupAXXX;


#endif // SMETAOBJECT_H
