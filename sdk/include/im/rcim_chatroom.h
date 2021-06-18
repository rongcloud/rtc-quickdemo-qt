/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_CHATROOM_H_
#define IMLIB_API_RCIM_CHATROOM_H_

#include "rcim_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 加入聊天室
 * @param engine                 引擎句柄
 * @param room_id                聊天室 id
 * @param history_messages_count 拉取历史消息条数
 * 最多拉取 50条
 * - = -1：不拉取历史消息
 * - = 0：拉取 10 条
 * @param cb                      回调函数指针
 * @param context                 用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_join_chatroom(HANDLE_IM_ENGINE engine,
                                   const char* room_id,
                                   int history_messages_count,
                                   rcim_general_callback cb,
                                   HANDLE context);

/**
 * @brief 退出聊天室
 * @param engine      引擎句柄
 * @param room_id     聊天室 id
 * @param cb          回调函数指针
 * @param context     用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_quit_chatroom(HANDLE_IM_ENGINE engine,
                                   const char* room_id,
                                   rcim_general_callback cb,
                                   HANDLE context);

/**
 * @brief 加入已经存在的聊天室
 * @param engine                 引擎句柄
 * @param room_id                聊天室 id
 * @param history_messages_count 拉取历史消息条数
 * 最多拉取 50条
 * - = -1：不拉取历史消息
 * - = 0：拉取 10 条
 * @param cb                     回调函数指针
 * @param context                用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_join_exist_chatroom(HANDLE_IM_ENGINE engine,
                                         const char* room_id,
                                         int history_messages_count,
                                         rcim_general_callback cb,
                                         HANDLE context);

/**
 * @brief 获取聊天室信息
 * @param engine   引擎句柄
 * @param room_id  聊天室 id
 * @param count    获取多少个用户信息，[0-20]
 * @param order    按加入聊天室的顺序获取用户
 *                 - RCIM_CHATROOM_USER_ORDER_ASC：升序
 *                 - RCIM_CHATROOM_USER_ORDER_DESC：降序
 * @param cb       回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_get_chatroom_info(HANDLE_IM_ENGINE engine,
                                       const char* room_id,
                                       int count,
                                       enum rc_chatroom_user_order order,
                                       rcim_get_chatroom_info_callback cb,
                                       HANDLE context);

/**
 * @brief  从服务器端获取聊天室的历史消息
 *         此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
 * @param engine   引擎句柄
 * @param room_id  聊天室 id
 * @param begin    记录时间，返回这个时间之前的最近 count 条消息
 * @param count    需要获取的消息数量，0 < count <= 200
 * @param order    查询顺序
 * - RCIM_CHATROOM_MESSAGES_ORDER_DESC：倒序，
 * - RCIM_CHATROOM_MESSAGES_ORDER_ASC：正序
 * @param cb       回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_get_remote_chatroom_history_messages(
    HANDLE_IM_ENGINE engine,
    const char* room_id,
    long long begin,
    unsigned count,
    enum rc_chatroom_messages_order order,
    rcim_get_remote_chatroom_history_messages_callback cb,
    HANDLE context);

/**
 * @brief 注册聊天室状态监听器
 * @param engine   引擎句柄
 * @param cb       回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_register_chatroom_status_listener(
    HANDLE_IM_ENGINE engine,
    rcim_chatroom_status_listener cb,
    HANDLE context);

/**
 * @brief 设置聊天室的状态信息
 * @param engine            引擎句柄
 * @param room_id           聊天室 id
 * @param key               设置的状态的 key
 * @param value             设置的状态的 value
 * @param auto_delete       用户掉线或退出时，是否自动删除该 key、value 值。
 * 注意：自动删除时不会发送通知
 * @param send_notification 是否需要发送通知
 * @param notify_string     通知的自定义字段，RC:chrmKVNotiMsg
 * 通知消息中 会包含此字段，最大长度 2 kb
 * @param cb                回调函数指针
 * @param context           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_set_chatroom_entry(HANDLE_IM_ENGINE engine,
                                        const char* room_id,
                                        const char* key,
                                        const char* value,
                                        bool auto_delete,
                                        bool send_notification,
                                        const char* notify_string,
                                        rcim_general_callback cb,
                                        HANDLE context);

/**
 * @brief  强制设置聊天室自定义属性
 * @param engine                            引擎句柄
 * @param room_id                           聊天室 id
 * @param key                               设置的状态的 key
 * @param value                             设置的状态的 value
 * @param auto_delete                       用户掉线或退出时，是否自动删除该
 * key、value 值。注意：自动删除时不会发送通知。
 * @param send_notification                 是否需要发送通知
 * @param notify_string                     通知的自定义字段，RC:chrmKVNotiMsg
 * 通知消息中 会包含此字段，最大长度 2 kb
 * @param cb                                回调函数指针
 * @param context                           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_force_set_chatroom_entry(HANDLE_IM_ENGINE engine,
                                              const char* room_id,
                                              const char* key,
                                              const char* value,
                                              bool auto_delete,
                                              bool send_notification,
                                              const char* notify_string,
                                              rcim_general_callback cb,
                                              HANDLE context);

/**
 * @brief 获取聊天室 key/value 状态列表
 * @param engine                      引擎句柄
 * @param room_id                     聊天室 id
 * @param status_list                 指向 key/value 列表的指针
 * @param count                       status_list 长度
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 *
 * @note  返回的status_list指向的指针如果有值，需要调用
 *               ::rcim_free_data_info_array 函数来释放。
 */
RCIMLIB_API int rcim_get_all_chatroom_entries(HANDLE_IM_ENGINE engine,
                                              const char* room_id,
                                              rc_data_info** status_list,
                                              int* count);

/**
 * @brief 获取聊天室 key/value 状态列表
 * @param engine       引擎句柄
 * @param room_id      聊天室 id
 * @param key          要获取的聊天室属性名称
 * @param status_info  指向 rc_data_info 结构指针的指针
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 *
 * @note  返回的 status_info 指向的指针如果有值，需要调用
 *               ::rcim_free_data_info 函数来释放。
 */
RCIMLIB_API int rcim_get_chatroom_entry_by_key(HANDLE_IM_ENGINE engine,
                                               const char* room_id,
                                               const char* key,
                                               rc_data_info** status_info);

/**
 * @brief 删除聊天室的某个状态值
 * @param engine             引擎句柄
 * @param room_id            聊天室 id
 * @param key                状态的 key
 * @param send_notification  是否发送通知
 * @param notify_string      通知的自定义字段，RC:chrmKVNotiMsg
 * 通知消息中会包含此字段，最大长度 2 kb
 * @param cb                 回调函数指针
 * @param context            用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */

RCIMLIB_API int rcim_delete_chatroom_entry(HANDLE_IM_ENGINE engine,
                                           const char* room_id,
                                           const char* key,
                                           bool send_notification,
                                           const char* notify_string,
                                           rcim_general_callback cb,
                                           HANDLE context);

/**
 * @brief 强制删除聊天室的某个状态值
 * @param engine            引擎句柄
 * @param room_id           聊天室 id
 * @param key               状态的 key
 * @param send_notification 是否发送通知
 * @param notify_string     通知的自定义字段，RC:chrmKVNotiMsg
 * 通知消息中 会包含此字段，最大长度 2 kb
 * @param cb                回调函数指针
 * @param context           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */

RCIMLIB_API int rcim_force_delete_chatroom_entry(HANDLE_IM_ENGINE engine,
                                                 const char* room_id,
                                                 const char* key,
                                                 bool send_notification,
                                                 const char* notify_string,
                                                 rcim_general_callback cb,
                                                 HANDLE context);
#ifdef __cplusplus
}
#endif

#endif  // IMLIB_API_RCIM_CHATROOM_H_
