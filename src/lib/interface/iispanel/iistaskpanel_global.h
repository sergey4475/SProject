#ifndef IISTASKPANEL_GLOBAL_H
#define IISTASKPANEL_GLOBAL_H

#include <Qt/qglobal.h>

//#ifdef QIIS_STATICLIB
//#  undef QIIS_SHAREDLIB
//#  define IISTASKPANEL_EXPORT
//#else
//#  ifdef QIIS_MAKEDLL
//#   define IISTASKPANEL_EXPORT __declspec(dllexport)
//#  else
//#   define IISTASKPANEL_EXPORT __declspec(dllimport)
//#  endif
//#endif

#if defined(LIB_LIBRARY)
#  define IISTASKPANEL_EXPORT __declspec(dllexport)
#else
#  define IISTASKPANEL_EXPORT __declspec(dllimport)
#endif


#endif // IISTASKPANEL_GLOBAL_H
