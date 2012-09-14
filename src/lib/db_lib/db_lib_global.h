#ifndef DB_LIB_GLOBAL_H
#define DB_LIB_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtSql>

#if defined(DB_LIB_LIBRARY)
#  define DB_LIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DB_LIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DB_LIB_GLOBAL_H
