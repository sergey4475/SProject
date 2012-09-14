#include "db_drivers.h"

db_drivers::db_drivers(QObject *parent) :
    QObject(parent)
{
}

// Получаем имя поля бд
QString db_drivers::fieldName(QSqlField *ftypedef){
    return ftypedef->name();
}

// Получаем длинну поля бд
int db_drivers::fieldWidth(QSqlField *ftypedef){
    return ftypedef->length();
}

// Получаем длину дробной части
int db_drivers::fieldDecimals(QSqlField *ftypedef){
    return ftypedef->precision();
}
