#ifndef DB_LIB_GLOBAL_H
#define DB_LIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtSql>

#define Q_SQLTable       QSqlTableModel
#define QSqlFieldInfo QSqlField

#if defined(DB_LIB_LIBRARY)
#  define DB_LIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DB_LIBSHARED_EXPORT Q_DECL_IMPORT
#endif



QChar   toLower(QChar c);
QString toLower(const QString &s);
char    toAscii(QChar c);
int     indexOf( const QString &str, const QString &find_str );
const char *toLocal8Bit(const QString &s);
QStringList split(const QString &div, const QString &str );
QString trimm(const QString &s);

#endif // DB_LIB_GLOBAL_H
