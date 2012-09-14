#include "db_drivers.h"

db_drivers::db_drivers(QObject *parent) :
    QObject(parent)
{
}

// �������� ��� ���� ��
QString db_drivers::fieldName(QSqlField *ftypedef){
    return ftypedef->name();
}

// �������� ������ ���� ��
int db_drivers::fieldWidth(QSqlField *ftypedef){
    return ftypedef->length();
}

// �������� ����� ������� �����
int db_drivers::fieldDecimals(QSqlField *ftypedef){
    return ftypedef->precision();
}
