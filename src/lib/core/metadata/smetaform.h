#ifndef SMETAFORM_H
#define SMETAFORM_H

#include "smetaobject.h"

class sMetaForm : public sMetaObject
{
Q_OBJECT
public:
    sMetaForm(sMetaObject *parent = 0);

    QString sourceCode();
    void setSourceCode( const QString &src );

    int  defaultMode();
    void setDefaultMode( int mode );

    QByteArray dialogue();
    void setDialogue( const QByteArray &d );

};

class sMetaForms: public sMetaGroup
{
Q_OBJECT
public:
    sMetaForms();
    sMetaForm * newForm(){
        return new sMetaForm(this);
    }

    sMetaForm *form( const QString &name ){
        return (sMetaForm*) child( name );
    }
    sMetaForm *form( int idx ){
        return (sMetaForm*) child( idx );
    }

    int formCount(){
        return childCount();
    }
public slots:
};


#endif // SMETAFORM_H
