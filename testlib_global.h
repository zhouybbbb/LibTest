#ifndef TESTLIB_GLOBAL_H
#define TESTLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TESTLIB_LIBRARY)
#define TESTLIB_EXPORT Q_DECL_EXPORT
#else
#define TESTLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // TESTLIB_GLOBAL_H
