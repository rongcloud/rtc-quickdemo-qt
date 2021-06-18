/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_COMMON_H_
#define IMLIB_API_RCIM_COMMON_H_

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef IMLIB_API_EXPORT

#define IMLIB_EXPORT_API __declspec(dllexport)
#ifdef IMLIB_DEVELOP
#define IMLIB_API
#else
#define IMLIB_API __declspec(dllexport)
#endif

#elif defined(IMLIB_API_IMPORT)

#define IMLIB_EXPORT_API __declspec(dllimport)
#ifdef IMLIB_DEVELOP
#define IMLIB_API
#else
#define IMLIB_API __declspec(dllimport)
#endif

#else
#define IMLIB_EXPORT_API
#define IMLIB_API
#endif
#elif defined(__GNUC__) && (__GNUC__ >= 4) && !defined(__APPLE__) && \
    (defined(IMLIB_API_EXPORT) || defined(IMLIB_API_IMPORT))
#define IMLIB_API
#define IMLIB_EXPORT_API __attribute__((visibility("default")))

#else
#define IMLIB_API
#define IMLIB_EXPORT_API __attribute__((visibility("default")))
#endif  // __GNUC__

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ASSERT
#define ASSERT(x) (void)0
#endif

#if !defined(_WIN32)
typedef void* HANDLE_IM_ENGINE;
typedef void* HANDLE;
#else
#include <Windows.h>
typedef HANDLE HANDLE_IM_ENGINE;
#define RCIM_ENGINE_HANDLE_DEF 1
#if _MSC_VER <= 1600
typedef long long int64_t;
#endif
#endif

#include "rcim_basetypes.h"
#endif  // IMLIB_API_RCIM_COMMON_H_
