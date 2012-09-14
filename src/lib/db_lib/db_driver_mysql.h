#ifndef DB_DRIVER_MYSQL_H
#define DB_DRIVER_MYSQL_H

#include "db_drivers.h"

class db_driver_mysql : public db_drivers
{
public:
    db_driver_mysql();

    QString sqlDriverName();
    QString fieldtype( const QString &qdstype,
            int width, int decimals = 0,
            bool notnull = false, bool primarykey = false, bool serial = false );

    int fieldWidth(QSqlFieldInfo *ftypedef );
    QString defaultDatabaseName(){ return "mysql";}
    QString queryCreateDatabase( const QString &name );
    QString queryDropIndex( const QString &tname, const QString &iname );

};

#endif // DB_DRIVER_MYSQL_H
