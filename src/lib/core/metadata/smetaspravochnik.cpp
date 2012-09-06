#include "smetaspravochnik.h"

sMetaSpravochnik::sMetaSpravochnik(sMetaObject *parent)
    :sMetaObject("Spravochnik", "", parent )
{
    setId( lastId() );
    setObjectName( QString("%1_%2").arg( tr("Spravochnik") ).arg( id() ) );
    addChild( &v_fields );
    addChild( &v_gfields );
    addChild( &v_forms );
}


sMetaFields * sMetaSpravochnik::fields()
{
    return &v_fields;
}



sMetaFields * sMetaSpravochnik::gfields()
{
    return &v_gfields;
}


sMetaForms * sMetaSpravochnik::forms()
{
    return &v_forms;
}


sMetaCatalogues::sMetaCatalogues()
:sMetaGroup("Spravochniki")
{

}
