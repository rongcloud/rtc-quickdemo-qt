/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_COMMON_H
#define RTCLIB_API_RCRTC_COMMON_H

#if defined(_WIN32) || defined(__CYGWIN__)

#ifdef RCRTCLIB_EXPORT
#define RCRTCLIB_API _declspec(dllexport)
#elif defined(RCRTCLIB_IMPORT)
#define RCRTCLIB_API _declspec(dllimport)
#else
#define RCRTCLIB_API
#endif

#elif defined(__GNUC__) && (__GNUC__ >= 4)
#if defined(RCRTCLIB_EXPORT) || defined(RCRTCLIB_IMPORT)
#define RCRTCLIB_API __attribute__((visibility("default")))
#else
#define RCRTCLIB_API
#endif
#else
#define RCRTCLIB_API
#define RCIMLIB_API
#endif  // __GNUC__

#endif
