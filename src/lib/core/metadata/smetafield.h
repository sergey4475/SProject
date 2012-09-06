#ifndef SMETAFIELD_H
#define SMETAFIELD_H

#include "smetaobject.h"

class sMetaField : public sMetaObject
{
    Q_OBJECT
    Q_ENUMS( FieldTypes )
    Q_PROPERTY( int  fieldtype    READ fieldType    SCRIPTABLE true )
    Q_PROPERTY( int  fieldsubtype READ fieldSubType SCRIPTABLE true )
    Q_PROPERTY( int  width        READ width        SCRIPTABLE true )
    Q_PROPERTY( int  decimals     READ decimals     SCRIPTABLE true )
    Q_PROPERTY( bool notnull      READ notNull      SCRIPTABLE true )
    Q_PROPERTY( bool notnegative  READ notNegative  SCRIPTABLE true )
    Q_PROPERTY( bool calcsumm     READ calcSumm     SCRIPTABLE true )
public:
    sMetaField( sMetaObject *parent = 0 );
    enum FieldTypes { Unknown, Char, String, Number, Date, Object, Document, Catalogue, Constanta };

    int fieldType();
    void setFieldType( FieldTypes t );

    int fieldSubType();
    void setFieldSubType( int st );

    int width();
    void setWidth( int w );

    int decimals();
    void setDecimals( int d );

    bool notNull();
    void setNotNull( bool f );

    bool notNegative();
    void setNotNegative( bool f );

    bool calcSumm();
    void setCalcSumm( bool f );

};

class sMetaFields: public sMetaGroup
{
Q_OBJECT
public:
    sMetaFields();
    sMetaField * newField(){ return new sMetaField( this );}
    sMetaField *field( const QString &name ){ return (sMetaField*) child( name );}
    sMetaField *field( int idx ){ return (sMetaField*) child( idx );}
    int fieldCount(){ return childCount(); }

public slots:


};


#endif // SMETAFIELD_H
