#ifndef STASERVER_GLOBAL_H
#define STASERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STASERVER_LIBRARY)
#  define STASERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define STASERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STASERVER_GLOBAL_H