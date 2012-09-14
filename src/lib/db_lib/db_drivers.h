#ifndef DB_DRIVERS_H
#define DB_DRIVERS_H

#include <QObject>
#include "db_lib_global.h"

class db_drivers : public QObject
{
    Q_OBJECT
public:
    explicit db_drivers(QObject *parent = 0);
    virtual QString sqlDriverName();
    // Функции для работы с полями БД
    virtual QString fieldName(QSqlFieldInfo *ftypedef );
    virtual int fieldWidth(QSqlFieldInfo *ftypedef);
    virtual int fieldDecimals(QSqlFieldInfo *ftypedef);
    virtual QString defaultDatabaseName(){ return "";}
    //Основные запросы для операций с БД
    virtual QString queryInitConnection( bool unicode );
    virtual QString queryCreateDatabase( const QString &name );
    virtual QString queryDropDatabase( const QString &name );
    virtual QString queryCreateTable( const QString &name, const QString &fields );
    virtual QString queryDropTable( const QString &name );
    virtual QString queryCreateIndex( const QString &name, const QString &iname, const QString &fields );
    virtual QString queryDropIndex( const QString &name, const QString &iname );
    virtual QString queryAlterTable( const QString &tname,
                                     const QString &fieldsnew, const QString &fieldsold,
                                     const QString &fieldsadd,const QString &fieldsdrop,
                                     const QString &fieldsmodifynew,const QString &fieldsmodifyold );


protected:
    virtual QString queryAlterTableDropField( const QString &tname, const QString &field );
    virtual QString queryAlterTableAddField( const QString &tname, const QString &field );
    virtual QString queryAlterTableModifyField( const QString &tname, const QString &field, const QString &oldfield = "" );


signals:
    
public slots:
    
};

#endif // DB_DRIVERS_H
