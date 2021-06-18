/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_STRUCTURE_H_
#define IMLIB_API_RCIM_STRUCTURE_H_

#include "rcim_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rc_data_info {
  char* key;
  char* value;
} rc_data_info;

typedef struct rc_chatroom_user_info {
  char* user_id;        //用户 id
  long long join_time;  //用户加入聊天室的时间
} rc_chatroom_user_info;

typedef struct rc_user_info {
  char* user_id;       //用户 id
  char* name;          //用户名
  char* portrait_uri;  //用户头像
  char* extra;         //附加信息
} rc_user_info;

typedef struct rc_mentioned_info {
  rc_mentioned_type type;  //消息类型
  char** user_ids;         //消息用户 id 列表
  int user_ids_len;        //消息用户 id 列表长度
  char* content;           //消息内容
} rc_mentioned_info;

struct rc_message_content;

typedef void (*fn_rcim_message_content_encoder)(
    struct rc_message_content* message,
    char buffer[],
    int* buf_len,
    bool* success);

typedef void (*fn_rcim_message_content_decoder)(struct rc_message_content*,
                                                const char* json_str,
                                                bool* success);

typedef struct rc_message_content* (*fn_rcim_message_content_alloc)();

typedef void (*fn_rcim_message_content_free)(
    struct rc_message_content* message);

typedef void (*fn_rcim_message_content_copy)(
    struct rc_message_content* dst_message,
    struct rc_message_content* src_message);

typedef const char** (*fn_rcim_message_content_search_fields)();

typedef struct st_message_content_vtable {
  //把消息结构的内容编码成 json 字符串返回
  fn_rcim_message_content_encoder encoder;

  //根据 json 字符串的内容给消息结构各字段赋值
  fn_rcim_message_content_decoder decoder;

  //申请对应消息类型的消息结构内存
  fn_rcim_message_content_alloc alloc;

  //消息结构在析构的时候调用的函数
  fn_rcim_message_content_free free;

  //复制现有的消息结构内容，返回新生成的消息指针
  fn_rcim_message_content_copy copy;

  fn_rcim_message_content_search_fields search_fields;
} t_message_content_vtable;

typedef struct rc_message_content {
  rc_user_info user;            //用户携带用户信息
  rc_mentioned_info mentioned;  //用于携带提醒消息
  char* extra;                  //用于扩展
  char* object_name;

  int persistent;  //消息的类型标记，@ref rc_message_persistent

  t_message_content_vtable vtable;
} rc_message_content;

typedef struct rc_message {
  rc_conversation_type conversation_type;  //会话类型
  char* target_id;                         //会话 id
  rc_message_direction direction;          //消息方向
  char* sender_id;                         //发送者 id
  rc_message_status status;                //消息状态
  int64_t sent_time;            //消息发送时间（服务端生成）
  rc_message_content* content;  //消息内容
  int64_t message_id;           //数据库中存储 id
  char* message_uid;            //服务生成的消息唯一标识
  char* sender_platform;        //发送端设备平台
  int64_t send_ack;             //发送消息的 ack 序号
} rc_message;

/**
 * text message structure
 */
typedef struct rc_text_message {
  rc_message_content content;
  char* text;
  int burn_duration;  //存续时长
} rc_text_message;

/**
 * typing message structure
 */
typedef struct rc_typing_message {
  rc_message_content content;
  char* data;
  char* typing_content_type;
} rc_typing_message;

/**
 * status message structure
 */
typedef struct rc_status_message {
  rc_message_content content;
  char* status_type;
  char* status_content;
} rc_status_message;

/******************************************
 * functions
 *****************************************/

/**
 * @brief 释放 rc_data_info 结构占用的内存
 * @param data              指向 rc_data_info 结构指针的指针
 */
RCIMLIB_API void rcim_free_data_info(rc_data_info** data);

/**
 * @brief 释放 rc_data_info 结构占用的内存
 * @param data_array        指向 rc_data_info 结构指针的指针
 * @param count             表示有多少数据项要释放
 */
RCIMLIB_API void rcim_free_data_info_array(rc_data_info** data_array,
                                           int count);

RCIMLIB_API void rcim_free_user_info(rc_user_info** user);

RCIMLIB_API void rcim_free_user_info_array(rc_user_info** user_array,
                                           int count);
/*
 **********************************************************
 * alloc/free/copy functions for message structures
 **********************************************************
 */

/**
 * @brief 创建一个 rc_message 封装的消息实例
 *
 * @param message_content 要嵌套的具体消息类型的消息结构内容
 * @param conv_type 会话类型
 * @param target_id 会话 id
 * @param alloc_content 是否申请内存用来存储 message_content 的值
 *
 * @return 指向创建的 rc_message 实例的指针
 */
RCIMLIB_API rc_message* rcim_alloc_message(rc_message_content* message_content,
                                           rc_conversation_type conv_type,
                                           const char* target_id,
                                           bool alloc_content);

/**
 * @brief 释放 rc_message 指针所占用的内存
 * @param message           指向 rc_message 指针的指针，内存释放后 rc_message
 * 指针的值被改为 NULL
 */
RCIMLIB_API void rcim_free_message(rc_message** message);

/**
 * @brief 释放 rc_message 指针（数组）的内存和相关资源
 * @param message_array     指向 rc_message 指针的指针，所指向的内存是连续的
 *                          rc_message 指针数组
 * @param count             表示指针数组的长度
 * @note  函数调用成功后，message_array 指向的指针值被修改为 NULL
 */
RCIMLIB_API void rcim_free_message_array(rc_message** message_array, int count);
/**
 * @brief
 * 复制消息内容到目标消息结构，传入的两个消息结构指针必须都指向相同的消息类型
 * @param dst         目标消息结构指针，必须是已经正确分配消息结构内存的指针
 * @param src         源消息结构指针，包含要被复制的消息内容
 */
RCIMLIB_API void rcim_copy_message_content(rc_message_content* dst,
                                           rc_message_content* src);

/**
 * @brief 释放消息结构实例所占的内存和相关资源
 * @param message_content   指向消息内容实例的指针的指针。要释放的具体消息类型
 *                          的指针被强制转换成 rc_message_content 类型的指针
 *
 * @note: 成功释放后，message 指向的指针修改为 NULL
 */
RCIMLIB_API void rcim_free_message_content(
    rc_message_content** message_content);

/*
 *****************************************************************\
 * alloc for specific type message
 *****************************************************************
 */

/**
 * @brief 在堆上创建一个文本消息结构实例，返回指向此实例的指针
 * @param text 文本消息包含的字符串
 * @return 指向创建的消息结构的指针
 */
RCIMLIB_API rc_text_message* rcim_alloc_text_message(const char* text);

/**
 * @brief 在堆上创建一个正在输入消息类型的结构实例，返回指向此实例的指针
 * @param data  消息携带的数据内容
 * @param content_type 消息内容类型
 * @return 指向创建的消息结构的指针
 */
RCIMLIB_API rc_typing_message* rcim_alloc_typing_message(
    const char* data,
    const char* content_type);

/**
 * @brief 在堆上创建一个状态消息类型的结构实例，返回指向此实例的指针
 * @param status_type       状态类型
 * @param status_content    状态消息携带的内容
 * @return 指向创建的消息结构的指针
 */
RCIMLIB_API rc_status_message* rcim_alloc_status_message(
    const char* status_type,
    const char* status_content);
#ifdef __cplusplus
}
#endif
#endif  // IMLIB_API_RCIM_STRUCTURE_H_
