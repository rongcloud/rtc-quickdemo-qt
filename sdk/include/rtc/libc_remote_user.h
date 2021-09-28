/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_REMOTE_USER_H_
#define RCRTCLIB_LIBC_REMOTE_USER_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 加入房间后，调用此函数订阅指定用户大流
 *
 * @param room_id          房间 id
 * @param remote_user_id   远端用户 id
 * @param callback         结果回调
 * @param context          用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_switch_to_normal_stream(const char* room_id,
                              const char* remote_user_id,
                              fn_rcrtc_general_callback callback,
                              HANDLE context);

/**
 * @brief 加入房间后，调用此函数订阅指定用户小流
 *
 * @param room_id         房间 id
 * @param remote_user_id  远端用户 id
 * @param callback        结果回调
 * @param context         用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_switch_to_tiny_stream(const char* room_id,
                            const char* remote_user_id,
                            fn_rcrtc_general_callback callback,
                            HANDLE context);

/**
 * @brief 加入房间后，调用此函数获取远端发布的所有音视频流
 *
 * @param room_id  房间 id
 * @param user_id  远端用户 id
 * @param stream   发布的音视频流集合
 * @param count    音视频流集合的个数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_remote_user_get_streams(const char* room_id,
                              const char* user_id,
                              HANDLE_STREAM stream[MAX_STREAM_COUNT],
                              int32_t* count);

/**
 * @brief 获取直播流（mcu的合流）
 *
 * @param room_id  房间 id
 * @param stream   发布的音视频直播合流集合（包括音视频流）
 * @param count    音视频流集合的个数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_get_live_streams(const char* room_id,
                       char live_user_id[MAX_STRING_LEN],
                       HANDLE_STREAM stream[MAX_STREAM_COUNT],
                       int32_t* count);

#ifdef __cplusplus
}
#endif

#endif
