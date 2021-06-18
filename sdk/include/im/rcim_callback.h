/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_CALLBACK_H_
#define IMLIB_API_RCIM_CALLBACK_H_

#include "rcim_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 连接服务器回调函数
 * @param context                       用户传入的上下文参数值，用于回调函数
 *                                      参见 rc_set_connection_callback
 * @param code                          结果码 0：成功，非 0 失败
 */
typedef void (*rcim_connection_callback)(HANDLE context,
                                         rc_connection_status code);

/**
 * @brief 发送消息回调函数
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @param message                       消息结构指针
 * @param code                          结果码 0：成功，非 0 失败
 */
typedef void (*rcim_send_message_callback)(HANDLE context,
                                           const struct rc_message* message,
                                           int code);

/**
 * @brief 接收消息回调函数
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @param message                       消息结构指针
 * @param left                          还有多少条消息？
 * @param offline                       是否离线消息
 * @param has_more                      是否还有更多
 */
typedef void (*rcim_recv_message_callback)(HANDLE context,
                                           const struct rc_message* message,
                                           int left,
                                           bool offline,
                                           bool has_more);

/**
 * @brief 回调函数
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @param code                          结果码 0：成功，非 0 失败
 * @param error_description             错误描述
 */
typedef void (*rcim_general_callback)(HANDLE context,
                                      int code,
                                      const char* error_description);

/**
 * @brief 从服务器获取聊天室历史消息的回调函数
 * @param context 用户传入的上下文参数值，用于回调函数
 * @param code 查询结果码, 0：成功
 * @param room_id 聊天室 id
 * @param messages 获取到的消息
 * @param count 获取到的消息数量
 * @param has_more 服务器上是否还有消息可以获取
 */
typedef void (*rcim_get_remote_chatroom_history_messages_callback)(
    HANDLE context,
    int code,
    const char* room_id,
    rc_message** messages,
    int count,
    bool has_more);

/**
 * @brief 获取聊天室信息回调函数
 * @param code 查询结果码, 0 ：成功
 * @param room_id 聊天室 id
 * @param member_count 聊天室成员总数
 * @param users 获取的成员 id 和加入时间
 * @param count 获取的成员数
 */
typedef void (*rcim_get_chatroom_info_callback)(int code,
                                                const char* room_id,
                                                int member_count,
                                                rc_chatroom_user_info* users,
                                                int count);

typedef enum {
  RCIM_CHATROOM_ID_EVENT = 1,         // 同步聊天室 kv 数据
  RCIM_CHATROOM_STATUS_EVENT = 2,     // 拉取变更的 kv 数据
  RCIM_CHATROOM_DESTROYED_EVENT = 3,  // 清理当前聊天室所有的 kv 数据
} enum_chatroom_status_event;

/**
 * @brief 聊天室状态变化和数据回调函数
 * @param room_id                       聊天室 id
 * @param status_kv                     聊天室状态信息的 kv 数组
 * @param kv_size                       kv 数组的长度
 * @param event                         标记回调函数代表的事件类型
 *
 */
typedef void (*rcim_chatroom_status_listener)(const char* room_id,
                                              char** status_kv,
                                              int kv_size,
                                              enum_chatroom_status_event event);

#ifdef __cplusplus
}
#endif

#endif  // IMLIB_API_RCIM_CALLBACK_H_
