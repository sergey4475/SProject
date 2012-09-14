#ifndef DB_DRIVERS_H
#define DB_DRIVERS_H

#include <QObject>
#include "db_lib_global.h"

class db_drivers : public QObject
{
    Q_OBJECT
public:
    explicit db_drivers(QObject *parent = 0);

    virtual QString fieldName(QSqlField *ftypedef );
    virtual int fieldWidth(QSqlField *ftypedef);
    virtual int fieldDecimals(QSqlField *ftypedef);

signals:
    
public slots:
    
};

#endif // DB_DRIVERS_H
