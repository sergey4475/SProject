#include "db_lib.h"

/*
* \brief Создает и инициализирует новый объект.
*
* \arg ct (in) Тип соединения с сервером данных.
* \arg db_name (in) Имя объекта. Используется как имя соединения QSqldataBase.
*/
db_lib::db_lib( const QString ct, const char *db_name, QObject *parent ): QObject(parent)
{
    if (!db_name) db_name = "Schema";
    setObjectName(db_name);
    p_drv=0;
    if ( isDriverAvailable( ct ) ) {
        p_drv = createDriver( ct );
        if ( p_drv ) p_db = QSqlDatabase::addDatabase( p_drv->sqlDriverName(), objectName() );
    }
//dd_name = "dd";
    setPrefix("");
}

db_lib::~db_lib(){
    QSqlDatabase::removeDatabase( objectName() );
}

bool db_lib::open(const QString &dbname,
                  const QString &dbuser,
                  const QString &dbpass,
                  const QString &dbhost,
                  int dbport){
    if ( !db() || !driver() ) return false;
    db()->setDatabaseName(dbname );
    db()->setUserName( dbuser );
    db()->setPassword( dbpass );
    db()->setHostName( dbhost );
    if ( dbport ) db()->setPort( dbport );
    return open();


}

bool db_lib::open()
{
    bool res = false;

    if ( db() && driver() )
    {
        res = db()->open();
        if ( res ) {
            if ( execList( splitQString("\n",driver()->queryInitConnection( true )))) res = false;
        }
    }
    return res;
}


QSqlDatabase* db_lib::db(){
    return &p_db;
}

// Получаем таблицу по имени таблицы
Q_SQLTable * db_lib::table( const QString & name )
{
    Q_SQLTable *t;

    if ( tableExists( name ) ) {
        t = new QSqlTableModel( this, *db() );
        t->setTable( name );
    } else {
        t = 0;
    }
    return t;
}

// Имя таблицы с префиксом
QString db_lib::tableName( const QString &name )
{
    return prefix +"_"+ name;
}

// Имя таблицы без префикса
QString db_lib::tableNameStripPrefix( const QString &name )
{
    if ( name.left( prefix.length() ) == prefix ) {
        return name.right( name.length()-prefix.length() );
    }
    return name;
}

bool db_lib::tableExists( const QString & name )
{
    QStringList list = db()->tables(QSql::Tables );
    QStringList::Iterator it = list.begin();
    while( it != list.end() ) {
        if ( lowerQString(*it) == lowerQString(name) ) return true;
        ++it;
    }
    return false;
}

QString db_lib::getPrefix() const
{
    return prefix;
}

void db_lib::setPrefix( const QString &namesp )
{
    if (db() && !db()->isOpen()) prefix = namesp;
}

bool db_lib::isDriverAvailable ( const QString & name )
{
    return getDrivers().contains( name ) >0;
}

db_drivers * db_lib::driver()
{
    return p_drv;
}

// Подключаем соответствеющий драйвер
db_drivers * db_lib::createDriver(const QString ctype){
    db_drivers *drv = 0;

    if ( ctype == "QMYSQL" ) drv = new db_driver_mysql();
//    if ( ctype == "QPOSTGRESQL" ) drv = new QDataSchemaDriverPostgreSQL();
//    if ( ctype == "QSQLITE" ) drv = new QDataSchemaDriverSqlite();
    return drv;
}


// Создание БД.

bool db_lib::databaseCreate( const QString &dbadmuser, const QString &dbadmpass )
{
    QString savename, savepass, savedb;
    bool res = false;

    if ( db() && driver() )
    {
        savename = db()->userName();
        savepass = db()->password();
        savedb = db()->databaseName();
        db()->setUserName( dbadmuser );
        db()->setPassword( dbadmpass );
        db()->setDatabaseName( driver()->defaultDatabaseName() );
        res = db()->open();
        if ( res ) {
            if ( execList( splitQString("\n", driver()->queryCreateDatabase( savedb ) ) ) ) res = false;
        }
        db()->setUserName( savename );
        db()->setPassword( savepass );
        db()->setDatabaseName( savedb );
    }
    return res;
}

// Удаление БД
bool db_lib::databaseDrop( const QString &dbadmuser, const QString &dbadmpass )
{
    QString savename, savepass, savedb;
    bool res = false;

    if ( db() && driver() )
    {
        savename = db()->userName();
        savepass = db()->password();
        savedb = db()->databaseName();
        db()->setUserName( dbadmuser );
        db()->setPassword( dbadmpass );
        db()->setDatabaseName( driver()->defaultDatabaseName() );
        res = db()->open();
        if ( res ) {
            if ( execList( splitQString("\n", driver()->queryDropDatabase( savedb ) ) ) ) res = false;
        }
        db()->setUserName( savename );
        db()->setPassword( savepass );
        db()->setDatabaseName( savedb );
    }
    return res;
}


// Функция выполнения списка запросов
int db_lib::execList( const QStringList &queryList, bool inTransaction )
{
    QSqlQuery query;
    int i, rc = 0;

        if ( inTransaction ) db()->transaction();
    for ( i=0; i< queryList.count(); i++ ) {
//		printf("QUERY %i:%s\n", i, (const char *) queryList[i] );
        query = db()->exec( queryList[ i ] );
        rc = checkSqlError( query );
                if ( rc ) {
                    printf("ERROR ON QUERY %i:%s\n", i, (const char *) queryList[i].toAscii() );
                    break;
                }
    }
        if ( rc && inTransaction ) db()->rollback();
        if ( !rc && inTransaction ) db()->commit();
    return rc;
}

// Функция проверяет результат выполнения запроса
//*\return 0 - без ошибок, 1 - есть ошибка.
int db_lib::checkSqlError( QSqlQuery &query )
{
    QString err="";
    if (query.lastError().type()!=QSqlError::NoError)
    {
        err = QString("SQLError %1 %2\n").arg(query.lastError().databaseText()).arg(query.lastError().driverText());
        fprintf(stderr, err.toAscii());
        return 1;
    }
    return 0;
}

// Получаем доступные драйвера
QStringList db_lib::getDrivers()
{
    int i;
    db_drivers *d;
    QStringList li, l;

    li << "QMYSQL";
    li << "QSQLITE";
    li << "QPOSTGRESQL";

    for (i=0; i<li.count(); i++) {
        d = createDriver( li[i] );
        if ( QSqlDatabase::isDriverAvailable( d->sqlDriverName() ) ) l << li[i];
        delete d;
    }
    return l;
}


QStringList db_lib::splitQString(const QString &div, const QString &str )
{
    return str.split( div );
}

QString db_lib::lowerQString(const QString &str )
{
    return str.toLower();
}


