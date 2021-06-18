/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_CLIENT_H_
#define IMLIB_API_RCIM_CLIENT_H_

#include "rcim_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 此函数必须作为第一个被调用的 rcim sdk 函数，返回引擎句柄
 * @param  app_key      融云官网开发者后台生成的应用标示
 * @param  navi_url     选择连接的导航地址传空指针则使用默认地址
 * @param  conf_path    本地配置存储路径，传空指针则使用当前路径。
 * 传入的路径表示跟平台相关，windows 平台使用 \ 分割符，mac 和
 * linux 平台使用 / 分割符。 相对路径和绝对 路径都可以使用。
 * @param  error        返回引擎创建不成功时的错误码
 * @return 引擎句柄
 *
 * @note  如果返回值是 NULL，表示出现了错误, 此时不能再继续调用 rcim sdk
 * 的其他函数
 */
RCIMLIB_API HANDLE_IM_ENGINE rcim_init(const char* app_key,
                                       const char* navi_url,
                                       const char* conf_path,
                                       int* error);

/**
 * @brief 释放 rcim_init 返回的句柄，此函数必须是最后调用的 rcim sdk 函数
 * @param engine    引擎句柄，必须对应调用 ::rcim_init 返回的引擎句柄
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_uninit(HANDLE_IM_ENGINE engine);

/**
 * @brief 持续返回与服务器的连接状态
 * @param engine                            引擎句柄
 * @param cb                                回调函数指针
 * @param context                           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_set_connection_callback(HANDLE_IM_ENGINE engine,
                                             rcim_connection_callback cb,
                                             HANDLE context);

/**
 * @brief 连接融云服务器,必须连接成功才能进行其它操作
 * @param engine                            引擎句柄
 * @param user_token                        代表个人身份的令牌，通过融云
 *                                          Server API 获得，详见官网链接的文档
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_connect(HANDLE_IM_ENGINE engine, const char* user_token);

/**
 * @brief 断开与融云服务器连接.
 * @param engine  引擎句柄
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_disconnect(HANDLE_IM_ENGINE engine);

/**
 * @brief 设置接收消息的回调函数
 * @param engine                            引擎句柄
 * @param cb                                回调函数指针
 * @param context                           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 */
RCIMLIB_API int rcim_set_recv_message_callback(HANDLE_IM_ENGINE engine,
                                               rcim_recv_message_callback cb,
                                               HANDLE context);

/**
 * @brief 设置发送消息的回调函数
 * @param engine                            引擎句柄
 * @param cb                                回调函数指针
 * @param context                           用户传入的上下文参数值，用于回调函数
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 */
RCIMLIB_API int rcim_set_send_message_callback(HANDLE_IM_ENGINE engine,
                                               rcim_send_message_callback cb,
                                               HANDLE context);

/**
 * @brief 发送消息
 * @param engine      引擎句柄
 * @param message     要发送的消息结构指针
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_send_message(HANDLE_IM_ENGINE engine, rc_message* message);

/**
 * @brief 发送定向消息
 *  
 * @param engine            引擎句柄
 * @param conv_type         发送消息的会话类型
 * @param target_id         发送消息的会话 id
 * @param user_id_array     接收消息的用户 id 列表
 * @param user_count        用户 id 列表的长度
 * @param content           消息的内容
 * @param push_content      接收方离线时需要显示的远程推送内容
 * @param push_data         接收方离线时需要在远程推送中携带的非显示数据
 * @param out_message       传入的指针不为 NULL 时，在调用成功后
 *                          指针指向发送的消息对象。
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 * @note
此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 *
 * @warning 此方法目前仅支持群组和讨论组。
 */
RCIMLIB_API int rcim_send_directional_message_content(
    HANDLE_IM_ENGINE engine,
    rc_conversation_type conv_type,
    const char* target_id,
    const char** user_id_array,
    int user_count,
    rc_message_content* content,
    const char* push_content,
    const char* push_data,
    rc_message** out_message);

/**
 * @brief 发送定向消息
 * @param engine            引擎句柄
 * @param message           要发送的消息实体，调用成功后里面的内容会有修改
 * @param user_id_array     接收消息的用户 id 列表
 * @param user_count        用户 id 列表的长度
 * @param push_content      接收方离线时需要显示的远程推送内容
 * @param push_data         接收方离线时需要在远程推送中携带的非显示数据
 *
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 *
 * @note
此方法用于在群组和讨论组中发送消息给其中的部分用户，其它用户不会收到这条消息。
 * @warning 此方法目前仅支持群组和讨论组。
 *
 */
RCIMLIB_API int rcim_send_directional_message(HANDLE_IM_ENGINE engine,
                                              rc_message* message,
                                              const char** user_id_array,
                                              int user_count,
                                              const char* push_content,
                                              const char* push_data);

/**
 * @brief 日志初始化接口
 * @param file_path                    日志文件输出路径，若为 NULL
 *                                     则只输出到屏幕
 * @param level                        日志输出等级。0 为最高级，输出最全；5
 * 为不输出
 */
RCIMLIB_API void rcim_set_log(const char* file_path, enum rcim_log_level level);

/**
 * @brief 获取会话中的草稿信息（用户输入但未发送的暂存消息）
 * @param  engine                      引擎句柄
 * @param  conv_type                   会话类型
 * @param  target_id                   会话 id
 * @param  draft                       指向 char* 的指针，存储的是草稿的文字内容
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 *
 */

RCIMLIB_API int rcim_get_text_message_draft(HANDLE_IM_ENGINE engine,
                                            rc_conversation_type conv_type,
                                            const char* target_id,
                                            char** draft);

/**
 * @brief 释放指向草稿内容的指针的内存
 * @param  draft 草稿的文字内容，释放内存后，指针的值被修改为 NULL
 */
RCIMLIB_API void rcim_free_text_message_draft(char** draft);

/**
 * @brief 保存草稿信息（用户输入但未发送的暂存消息）
 * @param  engine                      引擎句柄
 * @param  conv_type                   会话类型
 * @param  target_id                   会话 id
 * @param  content                     草稿的文字内容
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_save_text_message_draft(HANDLE_IM_ENGINE engine,
                                             rc_conversation_type conv_type,
                                             const char* target_id,
                                             const char* content);

/**
 * @brief 删除会话中的草稿信息（用户输入但未发送的暂存消息）
 * @param  engine                      引擎句柄
 * @param  conv_type                   会话类型
 * @param  target_id                   会话 id
 * @return
 * - RCIM_OK 成功
 * - RCIM_ERROR 错误
 * 具体错误码描述信息参见 \ref rc_message_error_code 定义
 */
RCIMLIB_API int rcim_clear_text_message_draft(HANDLE_IM_ENGINE engine,
                                              rc_conversation_type conv_type,
                                              const char* target_id);

#ifdef __cplusplus
}
#endif

#endif  // IMLIB_API_RCIM_CLIENT_H_
