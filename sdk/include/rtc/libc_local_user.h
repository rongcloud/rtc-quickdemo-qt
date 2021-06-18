/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_LOCAL_USER_H_
#define RCRTCLIB_LIBC_LOCAL_USER_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_USER_PROPERTY_COUNT 256

/**
 * @brief 加入房间后，调用此函数设置用户属性
 *
 * @param room_id       房间 id
 * @param value         值
 * @param key           key
 * @param object_name   自定义对象名称
 * @param message       自定义消息
 * @param callback      设置用户属性结果回调
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_local_user_set_attribute_value(const char* room_id,
                                     const char* value,
                                     const char* key,
                                     const char* object_name,
                                     const char* message,
                                     fn_rcrtc_general_callback callback,
                                     HANDLE context);

/**
 * @brief 加入房间后，调用此函数删除用户属性
 *
 * @param room_id      房间 id
 * @param keys         key 数组
 * @param object_name  自定义对象名称
 * @param message      自定义消息
 * @param callback     删除用户属性结果回调
 * @param context      用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_local_user_delete_attribute_value(
    const char* room_id,
    const char* keys[MAX_USER_PROPERTY_COUNT],
    const char* object_name,
    const char* message,
    fn_rcrtc_general_callback callback,
    HANDLE context);

/**
 * @brief 加入房间后，调用此函数获取用户属性
 *
 * @param room_id      房间 id
 * @param keys         key 数组
 * @param callback     用户属性结果回调
 * @param context      用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_local_user_get_attribute_value(const char* room_id,
                                     const char* keys[MAX_USER_PROPERTY_COUNT],
                                     fn_rcrtc_general_json_callback callback,
                                     HANDLE context);

#ifdef __cplusplus
}
#endif

#endif
