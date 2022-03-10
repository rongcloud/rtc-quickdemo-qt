/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RC_LIBC_COMMON_H
#define RC_LIBC_COMMON_H

#include "libc_basetypes.h"

#if defined(_WIN32) || defined(__CYGWIN__)

#ifdef RCIMLIB_EXPORT
#define RCIMLIB_API __declspec(dllexport)
#elif defined(RCIMLIB_IMPORT)
#define RCIMLIB_API __declspec(dllimport)
#else
#define RCIMLIB_API
#endif

#elif defined(__GNUC__) && (__GNUC__ >= 4)
#if defined(RCIMLIB_EXPORT) || defined(RCIMLIB_IMPORT)
#define RCIMLIB_API __attribute__((visibility("default")))
#else
#define RCIMLIB_API
#endif
#else
#define RCIMLIB_API
#endif  // __GNUC__

#endif
