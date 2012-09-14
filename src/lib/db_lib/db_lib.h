#ifndef DB_LIB_H
#define DB_LIB_H

#include "db_lib_global.h"
#include "db_drivers.h"
#include "db_driver_mysql.h"

class DB_LIBSHARED_EXPORT db_lib: public QObject{

Q_OBJECT

public:
    db_lib( const QString ctype, const char *db_name = 0, QObject *parent = 0 );
    ~db_lib();
    bool open( const QString &dbname,
            const QString &dbuser = "", const QString &dbpass = "",
            const QString &dbhost = "localhost", int dbport = 0 );

    bool open();
    void close();

    QSqlDatabase* db();

    bool databaseCreate( const QString &dbadmuser, const QString &dbadmpass );
    bool databaseDrop( const QString &dbadmuser, const QString &dbadmpass );

    db_drivers * driver();
    int execList( const QStringList &queryList, bool inTransaction = false);

    Q_SQLTable *table( const QString &name = QString::null );
    QString tableName( const QString &name );
    QString tableNameStripPrefix( const QString &name );
    bool tableExists( const QString & name );
    QString getPrefix() const;
    void setPrefix( const QString &namesp );

    int checkSqlError( QSqlQuery &query );

    bool isDriverAvailable ( const QString & name );
    QStringList getDrivers();
    db_drivers * createDriver(const QString ctype);

private:
    QSqlDatabase p_db;
    db_drivers *p_drv;
    QString p_dbname, p_dbuser, p_dbpass, p_dbtype, p_dbhost, prefix;
    int	p_dbport;

protected:
    QStringList splitQString(const QString &div, const QString &str );
    QString lowerQString(const QString &str );
};

#endif // DB_LIB_H
