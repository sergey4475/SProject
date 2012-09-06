#ifndef SMETASPRAVOCHNIK_H
#define SMETASPRAVOCHNIK_H

#include "smetaobject.h"
#include "smetafield.h"
#include "smetaform.h"

class sMetaSpravochnik : public sMetaObject
{
Q_OBJECT
public:
    sMetaSpravochnik(sMetaObject *parent = 0);

public slots:
    sMetaFields *fields();
    sMetaFields *gfields();
    sMetaForms  *forms();

private:
    sMetaFields      v_fields;
    sMetaFields      v_gfields;
    sMetaForms       v_forms;

};

class sMetaCatalogues: public sMetaGroup
{
Q_OBJECT
public:
    sMetaCatalogues();

    sMetaSpravochnik *newCatalogue(){ return new sMetaSpravochnik( this );}
    sMetaSpravochnik *catalogue( const QString &name ){ return (sMetaSpravochnik*) child( name );}
    sMetaSpravochnik *catalogue( int idx ){ return (sMetaSpravochnik*) child( idx );}
    int catalogueCount(){ return childCount(); }

public slots:


};


#endif // SMETASPRAVOCHNIK_H
