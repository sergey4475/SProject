#include "db_drivers.h"

db_drivers::db_drivers(QObject *parent) :
    QObject(parent)
{
}

// Получаем имя поля бд
QString db_drivers::fieldName(QSqlFieldInfo *ftypedef){
    return ftypedef->name();
}

// Получаем длинну поля бд
int db_drivers::fieldWidth(QSqlFieldInfo *ftypedef){
    return ftypedef->length();
}

// Получаем длину дробной части
int db_drivers::fieldDecimals(QSqlFieldInfo *ftypedef){
    return ftypedef->precision();
}

QString db_drivers::queryCreateDatabase(const QString &name){
    return QString("create database %1").arg( name );
}

QString db_drivers::queryDropDatabase(const QString &name){
    return QString("drop database %1").arg( name );
}

QString db_drivers::queryCreateTable( const QString &tname, const QString &fields ){
    return QString("create table %1 (%2)").arg( tname ).arg( QString( fields ).replace("\n",",") );
}

QString db_drivers::queryDropTable(const QString &name){
    return QString("drop table %1").arg( name );
}

QString db_drivers::queryCreateIndex( const QString &name, const QString &iname, const QString &fields )
{
    return QString("create index %1 on %2 (%3)").arg( iname ).arg( name ).arg( fields );
}

QString db_drivers::queryDropIndex( const QString &/*tname*/, const QString &iname )
{

    return QString("drop index %1").arg( iname );
}

QString db_drivers::queryAlterTable( const QString &tname,
                                    const QString &/*fieldsnew*/, const QString &/*fieldsold*/,
                                    const QString &fieldsadd,const QString &fieldsdrop,
                                    const QString &fieldsmodifynew,const QString &fieldsmodifyold )
{
    int i;
    QStringList fl;
    QString query = "";
    QString f;

    // Для добавления полей
    fl = split( "\n", fieldsadd );
    for (i = 0; i < fl.count(); i++ ){
        if ( !query.isEmpty()) query.append("\n");
        f = trimm( fl[i] );
        if ( !f.isEmpty() ) query.append( queryAlterTableAddField( tname, f ) );
    }
    // Для удаления полей
    fl = split( "\n", fieldsdrop );
    for (i = 0; i < fl.count(); i++ ){
        if ( !query.isEmpty()) query.append("\n");
        f = trimm( fl[i] );
        if ( !f.isEmpty() ) query.append( queryAlterTableDropField( tname, fl[i] ) );
    }
    // Для изменения полей
    fl = split( "\n", fieldsmodifynew );
    for (i = 0; i < fl.count(); i++ ){
        if ( !query.isEmpty()) query.append("\n");
        query.append( queryAlterTableModifyField( tname, fl[i], fieldsmodifyold.section("\n", i, i ) ) );
    }
    return query;
}


QString db_drivers::queryAlterTableDropField( const QString &tname, const QString &field )
{
    return QString("alter table %1 drop column %2\n").arg( tname ).arg( field.section(" ",0,0) );
}


QString db_drivers::queryAlterTableAddField(const QString &tname, const QString &field )
{
    return QString("alter table %1 add column %2\n").arg( tname ).arg( field );
}


QString db_drivers::queryAlterTableModifyField( const QString &tname, const QString &field, const QString &/*oldfield*/ )
{
    return QString("alter table %1 modify column %2\n").arg( tname ).arg( field );
}

QString db_drivers::queryInitConnection( bool /*unicode*/ )
{
    return "";
}

QString db_drivers::sqlDriverName()
{
    return "";
}



