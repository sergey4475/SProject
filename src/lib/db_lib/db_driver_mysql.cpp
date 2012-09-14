#include "db_driver_mysql.h"

db_driver_mysql::db_driver_mysql()
{
}


QString db_driver_mysql::sqlDriverName()
{
    return "QMYSQL3";
}

QString db_driver_mysql::fieldtype( const QString &qdstype,
        int width, int decimals,
        bool notnull, bool primarykey, bool serial )
{
    QString dt="";
    char t=' ';

    t = toAscii( toLower( qdstype[0] ) );
    switch ( t ) {
    case 'i':
            dt = QString("int");
            break;
        case 'l':
            dt = QString("bigint");
            break;
        case 'c':
            dt = QString("char(%1)").arg( width );
            break;
        case 's':
            dt = QString("varchar(%1)").arg( width );
            break;
        case 'n':
            dt = QString("decimal(%1,%2)").arg( width ).arg( decimals );
            break;
        case 'd':
            dt = QString("datetime");
            break;
        case 'o':
            dt = QString("bigint");
            break;
        default:
            dt = "";
            break;
        }
        if ( notnull ) dt.append(" not null" );
        if ( serial ) dt.append(" auto_increment");
        if ( primarykey ) dt.append(" PRIMARY KEY" );
        return dt;
}

int db_driver_mysql::fieldWidth( QSqlFieldInfo *ftypedef )
{
    int w;

    w = ftypedef->length() - ftypedef->precision();
    if ( ftypedef->precision() == 0 ) w--;
    return w;
}
QString db_driver_mysql::queryCreateDatabase( const QString &name )
{
    return QString("create database %1 character set utf8").arg( name );
}
QString db_driver_mysql::queryDropIndex( const QString &tname, const QString &iname )
{

    return QString("drop index %1 on %2").arg( iname ).arg(tname);
}
