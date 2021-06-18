/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

#ifndef RC_LIBC_BASETYPES_H_
#define RC_LIBC_BASETYPES_H_

#include <sys/types.h>

#ifndef _MSC_VER
#include <stdint.h>
#endif

/* define int types*/
#if defined(__GNUC__)

#ifndef _STDINT_H

/* FreeBSD has these C99 int types defined in /sys/inttypes.h already */
#ifndef _SYS_TYPES_H
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#else
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;
#endif  // _SYS_TYPES_H

#endif  // _STDINT_H

#elif defined(_MSC_VER)
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#if _MSC_VER <= 1600
typedef long long int64_t;
#endif
#endif  // COMPILER_GCC/COMPILER_MSVC

#if !defined(_SYSTEM_BUILD) && defined(WIN32)
#pragma warning(disable : 4068)
//#pragma system_include
#endif

/* C99 Boolean types for compilers without C99 support */
/* http://www.opengroup.org/onlinepubs/009695399/basedefs/stdbool.h.html */
#if !defined(__cplusplus)

#ifndef bool
#define bool _Bool
#endif

#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#define __bool_true_false_are_defined 1

#endif

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
typedef void* HANDLE;
#else
#include <Windows.h>
#endif  // _WIN32

typedef HANDLE HANDLE_IM_ENGINE;

#endif
