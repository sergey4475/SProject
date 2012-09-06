#include "smetafield.h"

sMetaField::sMetaField( sMetaObject *parent )
    :sMetaObject("MetaField","", parent )
{
    setId(lastId());
    setObjectName(QString("%1_%2").arg(tr("Field")).arg( id()));
    setFieldType(Unknown);
    setFieldSubType( 0 );
    setWidth( 0 );
    setDecimals( 0 );
    setNotNull( false );
    setNotNegative( false );
    setCalcSumm( false );
}

int sMetaField::fieldType()
{
    return attr("type").toInt();
}

void sMetaField::setFieldType(FieldTypes t)
{
    setAttr( "type", t );
}

int sMetaField::fieldSubType()
{
    return attr("subtype").toInt();
}


void sMetaField::setFieldSubType( int st )
{
    setAttr( "subtype", st );
}


int sMetaField::width()
{
    return attr("width").toInt();
}


void sMetaField::setWidth( int w )
{
    setAttr( "width", w );
}

int sMetaField::decimals()
{
    return attr("decimals").toInt();
}

void sMetaField::setDecimals( int d )
{
    setAttr( "decimals", d );
}

bool sMetaField::notNull()
{
    return attr("notnull").toBool();
}

void sMetaField::setNotNull( bool f )
{
    setAttr( "notnull", f );
}

bool sMetaField::notNegative()
{
    return attr("notnegative").toBool();
}


void sMetaField::setNotNegative( bool f )
{
    setAttr( "notnegative", f );
}

bool sMetaField::calcSumm()
{
    return attr("calcsumm").toBool();
}

void sMetaField::setCalcSumm( bool f )
{
    setAttr( "calcsumm", f );
}

sMetaFields::sMetaFields()
    :sMetaGroup("MetaFields")
{

}

