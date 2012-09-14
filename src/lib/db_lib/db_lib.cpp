#include "db_lib.h"


db_lib::db_lib(QString db_name)
{
    p_db = QSqlDatabase::addDatabase("QSLITE",db_name);
}

bool db_lib::open(const QString &dbname,
                  const QString &dbuser,
                  const QString &dbpass,
                  const QString &dbhost,
                  int dbport){
    if ( !p_db || !driver() ) return false;
    db()->setDatabaseName( dbname );
    db()->setUserName( dbuser );
    db()->setPassword( dbpass );
    db()->setHostName( dbhost );
    if ( dbport ) db()->setPort( dbport );
    return open();


}
