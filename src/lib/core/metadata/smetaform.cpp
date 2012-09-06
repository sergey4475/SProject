#include "smetaform.h"

sMetaForm::sMetaForm( sMetaObject *parent )
    :sMetaObject("MetaForm", "", parent )
{
    setSourceCode(
    "function on_formstart()\n{\n}\n\n"
    "function on_formstop()\n{\n}\n\n"
    "function on_button( name )\n{\n}\n\n"
    "function on_valuechanged( name, value )\n{\n}\n\n"
    "function on_tabupdate( row, col, tablename )\n{\n}\n\n"
    "function on_tablerow( tablename )\n{\n}\n\n"
    "function on_event( source, data )\n{\n}\n\n"
    "function on_tabrowselected( tablename, uid )\n{\n}\n\n"
    "function on_conduct()\n{\n}\n\n"
    );
    setDefaultMode( 0 );
}


QString sMetaForm::sourceCode()
{
    return attr("sourcecode").toString();
}

void sMetaForm::setSourceCode( const QString &src )
{
    setAttr( "sourcecode", src );
}

int sMetaForm::defaultMode()
{
    return attr("defaultmode").toInt();
}

void sMetaForm::setDefaultMode( int mode )
{
    setAttr( "defaultmode", mode );
}

QByteArray sMetaForm::dialogue()
{
    return attr("dialogue").toByteArray();
}

void sMetaForm::setDialogue( const QByteArray &d )
{
    setAttr( "dialogue", d );
}


sMetaForms::sMetaForms()
    :sMetaGroup("MetaForms")
{

}
