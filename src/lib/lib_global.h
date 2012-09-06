#ifndef LIB_GLOBAL_H
#define LIB_GLOBAL_H

#include <QtCore/qglobal.h>

//#if defined(LIB_LIBRARY)
//#  define LIBSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define LIBSHARED_EXPORT Q_DECL_IMPORT
//#endif

#if defined(LIB_LIBRARY)
#  define LIBSHARED_EXPORT __declspec(dllexport)
#else
#  define LIBSHARED_EXPORT __declspec(dllimport)
#endif


#endif // LIB_GLOBAL_H
