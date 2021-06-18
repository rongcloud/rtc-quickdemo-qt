/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

#include "libc_basetypes.h"

#ifndef RC_LIBC_COMMON_H_
#define RC_LIBC_COMMON_H_

#if defined(_WIN32) || defined(__CYGWIN__)

#ifdef RCRTCLIB_EXPORT
#define RCRTCLIB_API _declspec(dllexport)
#elif defined(RCRTCLIB_IMPORT)
#define RCRTCLIB_API _declspec(dllimport)
#else
#define RCRTCLIB_API
#endif

#ifdef RCIMLIB_EXPORT
#define RCIMLIB_API __declspec(dllexport)
#elif defined(RCIMLIB_IMPORT)
#define RCIMLIB_API __declspec(dllimport)
#else
#define RCIMLIB_API
#endif

#elif defined(__GNUC__) && (__GNUC__ >= 4)
#if defined(RCRTCLIB_EXPORT) || defined(RCRTCLIB_IMPORT)
#define RCRTCLIB_API __attribute__((visibility("default")))
#else
#define RCRTCLIB_API
#endif
#if defined(RCIMLIB_EXPORT) || defined(RCIMLIB_IMPORT)
#define RCIMLIB_API __attribute__((visibility("default")))
#else
#define RCIMLIB_API
#endif
#else
#define RCRTCLIB_API
#define RCIMLIB_API
#endif  // __GNUC__

#endif
