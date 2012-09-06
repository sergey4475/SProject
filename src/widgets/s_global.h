#ifndef S_GLOBAL_H
#define S_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QColor>

#if defined(LIB_LIBRARY)
#  define Q_S_EXPORT Q_DECL_EXPORT
#else
#  define Q_S_EXPORT Q_DECL_IMPORT
#endif


#endif // S_GLOBAL_H
