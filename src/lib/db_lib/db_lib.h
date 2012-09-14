#ifndef DB_LIB_H
#define DB_LIB_H

#include "db_lib_global.h"

class DB_LIBSHARED_EXPORT db_lib: public QObject{

Q_OBJECT

public:
    db_lib(QString db_name);

    bool open( const QString &dbname,
            const QString &dbuser = "", const QString &dbpass = "",
            const QString &dbhost = "localhost", int dbport = 0 );

    bool open();
    void close();


private:
    QSqlDatabase p_db;
    QString p_dbname, p_dbuser, p_dbpass, p_dbtype, p_dbhost;
    int	p_dbport;

};

#endif // DB_LIB_H
