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
    p_db->setDatabaseName( dbname );
    p_db->setUserName( dbuser );
    p_db->setPassword( dbpass );
    p_db->setHostName( dbhost );
    if ( dbport ) p_db->setPort( dbport );
    return open();


}
