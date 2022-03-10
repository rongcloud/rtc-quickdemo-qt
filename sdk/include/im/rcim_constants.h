/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef IMLIB_API_RCIM_CONSTANTS_H
#define IMLIB_API_RCIM_CONSTANTS_H

#include "libc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum rcim_log_level {
  RCIM_LOG_LEVEL_SENSITIVE,
  //最不重要，需要关注函数的构造、析构；关键流程之高频函数的关键位置。
  RCIM_LOG_LEVEL_VERBOSE,
  //不重要，重要逻辑中函数的构造、析构；关键流程之的关键位置。
  RCIM_LOG_LEVEL_INFO,
  //一般，默认会在 debug
  //版本中出现；关键位置需要显示关键信息的地方，不建议加在循环等频繁调用的位置。
  RCIM_LOG_LEVEL_WARNING,
  //警告，需要提醒开发者注意的位置，默认会在 release 版本出现。
  RCIM_LOG_LEVEL_ERROR,
  //错误，需要提醒用户注意的位置，需要有后续处理。
  RCIM_LOG_LEVEL_NONE,
} rcim_log_level;

typedef enum rc_connection_status {
  RCIM_CONNECTION_UNINITIALIZED = -1,
  /**
   * 连接成功
   */
  RCIM_CONNECTION_CONNECTED = 0,
  /**
   * 重新连接成功
   */
  RCIM_CONNECTION_RECONNECTED = 1,
  /**
   * 账号在其他设备上登录，此设备被踢下线
   */
  RCIM_CONNECTION_KICKED_OFF = 6,
  /**
   * 服务异常
   */
  RCIM_CONNECTION_SERVER_INVALID = 8,
  /**
   * 用户连接受限
   */
  RCIM_CONNECTION_VALIDATE_FAILURE = 9,
  /**
   * 正在建立连接
   */
  RCIM_CONNECTION_CONNECTING = 10,
  /**
   * 连接未建立或者已断开
   */
  RCIM_CONNECTION_UNCONNECTED = 11,
  /**
   * 用户已退出登录
   */
  RCIM_CONNECTION_SIGN_OUT = 12,
  /**
   * 用户被封禁
   */
  RCIM_CONNECTION_USER_IS_BLOCKED = 13,
  /**
   * 内存分配失败
   */
  RCIM_CONNECTION_NAVI_MALLOC_ERROR = 30000,
  /**
   * 获取导航响应失败
   */
  RCIM_CONNECTION_NAVI_RESOURCE_ERROR = 30007,
  /**
   * 导航返回数据无效
   */
  RCIM_CONNECTION_NAVI_SERVER_NOT_FOUND = 30008,
  /**
   * TCP 连接失败
   */
  RCIM_CONNECTION_TCP_FAILED = 30010,
  /**
   * PING 超时
   * SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_PONG_TIMEOUT = 30013,
  /**
   * 连接ACK超时
   * 连接相关的错误码，SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_ACK_TIMEOUT = 31000,
  /**
   * 信令版本错误
   * 连接相关的错误码，SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_PROTO_VERSION_ERROR = 31001,
  /**
   * AppKey 错误
   * SDK 不会重连
   */
  RCIM_CONNECTION_ID_REJECT = 31002,
  /**
   * 服务器当前不可用（预留）
   * SDK 不会重连
   */
  RCIM_CONNECTION_SEVER_UNAVAILABLE = 31003,
  /**
   * 1 appkey 和 token 不匹配
   * 2 token 过期
   * SDK 不会重连
   */
  RCIM_CONNECTION_TOKEN_INCORRECT = 31004,
  /**
   * 连接重定向
   * SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_REDIRECTED = 31006,
  /**
   *BUNDLEID不正确
   * 请检查您 App 的 bundle id/包名是否正确。
   * SDK 不会重连
   */
  RCIM_CONNECTION_PACKAGE_NAME_INVALID = 31007,
  /**
   * APPKEY 被封禁或已删除
   * 请检查您使用的APPKEY是否被封禁或已删除。
   * SDK 不会重连
   */
  RCIM_CONNECTION_APP_BLOCKED_OR_DELETED = 31008,
  /**
   * 用户被封禁
   * 请检查您使用的TOKEN是否正确，以及对应的 user_id 是否被封禁。
   * SDK 不会重连
   */
  RCIM_CONNECTION_USER_BLOCKED = 31009,
  /**
   * 用户被踢下线
   * 当前用户在其他设备上登录，此设备被踢下线
   * SDK 不会重连
   */
  RCIM_CONNECTION_KICKED = 31010,
  /**
   * TOKEN 过期
   * SDK 不会重连
   */
  RCIM_CONNECTION_TOKEN_EXPIRED = 31020,
  /**
   * TOKEN 不允许在此设备使用
   * SDK 不会重连
   */
  RCIM_CONNECTION_TOKEN_INVALID_FOR_DEVICE = 31021,
  /**
   * 账号在其他设备登录
   * SDK 不会重连
   */
  RCIM_CONNECTION_LOGIN_OTHER_DEVICE = 31023,
  /**
   * 同时连接的用户数达到限制
   * SDK 不会重连
   */
  RCIM_CONNECTION_CONCURRENT_USER_LIMIT = 31024,
  /**
   * TCP 连接断开
   */
  RCIM_CONNECTION_DISCONNECTED = 30011,
  /*!
   * TCP 连接被重置
   * SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_TCP_RESET = 32054,
  /**
   * TCP 连接被拒绝
   * SDK会做好自动重连，开发者无须处理。
   */
  RCIM_CONNECTION_TCP_REFUSED = 32061,
  /**
   * 连接环境不正确（融云公有云 SDK 无法连接到私有云环境）
   * 请确认需要连接的环境，使用正确 SDK 版本。
   * SDK 不会重连
   */
  RCIM_CONNECTION_ENVIRONMENT_ERROR = 34005,
} rc_connection_status;

typedef enum rc_message_status {
  /**
   * 消息未读
   */
  RCIM_MESSAGE_STATUS_RECEIVE_UNREAD = 0,
  /**
   * 消息已读
   */
  RCIM_MESSAGE_STATUS_RECEIVE_READ = 1,
  /**
   * 语音消息已听
   */
  RCIM_MESSAGE_STATUS_RECEIVE_LISTENED = 2,
  /**
   *该消息已经被其他登录的终端收取过
   */
  RCIM_MESSAGE_STATUS_RECEIVE_RETRIEVED = 8,
  /**
   * 消息正在发送中
   */
  RCIM_MESSAGE_STATUS_SENT_SENDING = 10,
  /**
   * 消息发送失败
   */
  RCIM_MESSAGE_STATUS_SENT_FAILED = 20,
  /**
   * 消息发送成功
   */
  RCIM_MESSAGE_STATUS_SENT_SENT = 30,
  /**
   * 消息回执, 对方已读
   */
  RCIM_MESSAGE_STATUS_SENT_READ = 50,
} rc_message_status;

typedef enum rc_message_persistent {
  /**
   * 不存储本地数据库，不计入未读数
   */
  RCIM_MESSAGE_PERSISTENT_NONE = 0,
  /**
   * 存储本地数据库，不计入未读数
   */
  RCIM_MESSAGE_PERSISTENT_PERSIST = 1,
  /**
   * 存储本地数据库，计入未读数
   */
  RCIM_MESSAGE_PERSISTENT_PERSIST_COUNT = 3,
  /**
   * 不存储本地数据库，不计入未读数
   * 在线可以收取，不在线消息会被抛弃
   */
  RCIM_MESSAGE_PERSISTENT_STATUS = 16
} rc_message_persistent;

typedef enum rc_conversation_type {
  /**
   * 无效类型
   */
  RCIM_CONVERSATION_INVALID = 0,
  /**
   * 单聊
   */
  RCIM_CONVERSATION_PRIVATE = 1,
  /**
   * 群组
   */
  RCIM_CONVERSATION_GROUP = 3,
  /**
   * 聊天室
   */
  RCIM_CONVERSATION_CHATROOM = 4,
  /**
   * 客服
   */
  RCIM_CONVERSATION_CUSTOMER_SERVICE = 5,
  /**
   * 系统消息， SDK 不支持发送此类型消息，只能接收
   */
  RCIM_CONVERSATION_SYSTEM = 6,
  /**
   * 应用内公众服务平台
   */
  RCIM_CONVERSATION_APP_SERVICE = 7,
  /**
   * 应用间公众服务平台
   */
  RCIM_CONVERSATION_PUBLIC_SERVICE = 8,
  /**
   * 推送服务会话
   */
  RCIM_CONVERSATION_PUSH_SERVICE = 9,

  /**
   * RTC 会话
   */
  RCIM_CONVERSATION_RTC = 12,

  RCIM_CONVERSATION_SUPPORT_TYPE = RCIM_CONVERSATION_RTC + 1,
} rc_conversation_type;

typedef enum rc_message_direction {
  /**
   * 消息是发送的
   */
  RCIM_MESSAGE_DIRECTION_SEND = 1,
  /**
   * 消息是接收的
   */
  RCIM_MESSAGE_DIRECTION_RECEIVE = 2,
} rc_message_direction;

typedef enum rc_message_error_code {
  RCIM_ERROR = -1,
  RCIM_OK = 0,
  /**
   * 被对方加入黑名单，发送消息失败
   */
  RCIM_REJECTED_BY_BLACKLIST = 405,
  /**
   * 发送消息频率过高，1 秒钟最多只允许发送5条消息
   */
  RCIM_SEND_MESSAGE_FREQUENCY_OVERRUN = 20604,
  /**
   *当前用户不在该讨论组中
   */
  RCIM_NOT_IN_DISCUSSION = 21406,
  /**
   * 当前用户不在该群组中
   */
  RCIM_NOT_IN_GROUP = 22406,
  /**
   * 当前用户在群组中已被禁言
   */
  RCIM_FORBIDDEN_IN_GROUP = 22408,
  /**
   *当前用户不在该聊天室中
   */
  RCIM_NOT_IN_CHATROOM = 23406,
  /**
   * 当前用户在该聊天室中已被禁言
   */
  RCIM_FORBIDDEN_IN_CHATROOM = 23408,
  /**
   *当前用户已被踢出并禁止加入聊天室。被禁止的时间取决于服务端调用踢出接口时传入的时间。
   */
  RCIM_KICKED_FROM_CHATROOM = 23409,
  /**
   * 聊天室不存在
   */
  RCIM_CHATROOM_NOT_EXIST = 23410,
  /**
   * 聊天室成员超限，默认聊天室成员没有人数限制，但是开发者可以提交工单申请针对
   * App Key
   * 进行聊天室人数限制，在限制人数的情况下，调用加入聊天室的接口时人数超限，就会返回此错误码
   */
  RCIM_CHATROOM_IS_FULL = 23411,
  /**
   * 聊天室接口参数无效。请确认参数是否为空或者有效。
   */
  RCIM_PARAMETER_INVALID_CHATROOM = 23412,
  /**
   * 聊天室云存储业务未开通
   */
  RCIM_ROAMING_SERVICE_UNAVAILABLE_CHATROOM = 23414,
  /**
   * 超过聊天室的最大状态设置数，1 个聊天室默认最多设置 100 个
   */
  RCIM_EXCEED_MAX_KV_SIZE = 23423,
  /**
   * 聊天室中非法覆盖状态值，状态已存在，没有权限覆盖
   */
  RCIM_TRY_OVERWRITE_INVALID_KEY = 23424,
  /**
   * 超过聊天室中状态设置频率，1 个聊天室 1 秒钟最多设置和删除状态 100 次
   */
  RCIM_EXCEED_MAX_CALL_API_SIZE = 23425,
  /**
   * 聊天室状态存储功能没有开通，请联系商务开通
   */
  RCIM_KV_STORE_NOT_AVAILABLE = 23426,
  /**
   * 聊天室状态值不存在
   */
  RCIM_KEY_NOT_EXIST = 23427,
  /**
   * 当前连接不可用（连接已经被释放）
   */
  RCIM_CHANNEL_INVALID = 30001,
  /**
   * 客户端发送消息请求，融云服务端响应超时。
   */
  RCIM_MESSAGE_RESPONSE_TIMEOUT = 30003,
  /**
   * SDK没有初始化 在使用SDK任何功能之前，必须先Init。
   */
  RCIM_CLIENT_NOT_INIT = 33001,
  /**
   * 打开数据库错误
   * 数据库路径中包含 user_id，如果获取 token 时传入的 user_id
   * 包含特殊字符，有可能导致该错误。
   */
  RCIM_DATABASE_ERROR = 33002,
  /**
   * 接口调用时传入的参数错误
   */
  RCIM_INVALID_PARAMETER = 33003,
  /**
   * 历史消息云存储业务未开通。可以在融云开发者后台中开启该服务。
   */
  RCIM_MESSAGE_ROAMING_SERVICE_UNAVAILABLE = 33007,
  /**
   * 无效的应用间公众号。(由会话类型和 id 所标识的公众号会话是无效的)
   */
  RCIM_INVALID_OFFICIAL_ACCOUNT_MP = 29101,
  /**
   * 应用间公众号已关注
   */
  RCIM_OFFICIAL_ACCOUNT_MP_FOLLOWED_BY_DEFAULT = 29102,
  /**
   * 无效的应用内公众号。(由会话类型和 id 所标识的公众号会话是无效的)
   */
  RCIM_INVALID_OFFICIAL_ACCOUNT_MC = 29201,
  /**
   * 应用内公众号已关注
   */
  RCIM_OFFICIAL_ACCOUNT_MC_FOLLOWED_BY_DEFAULT = 29202,
  /**
   * 消息大小超限，消息体（序列化后的内容）最大128K Bytes。
   */
  RCIM_MESSAGE_SIZE_OUT_OF_LIMIT = 30016,
  /**
   * 撤回消息参数无效。请确认撤回消息参数是否正确。
   */
  RCIM_RECALL_MESSAGE_PARAMETER_INVALID = 25101,
  /**
   * 用户设置参数无效。请确认设置参数是否正确。
   */
  RCIM_PUSH_SETTING_PARAMETER_INVALID = 26001,
  /**
   * 操作不支持。仅私有云有效，服务端禁用了该操作。
   */
  RCIM_OPERATION_NOT_SUPPORT = 20606,
  /**
   * 发送的消息中包含敏感词 （发送方发送失败，接收方不会收到消息）
   */
  RCIM_MESSAGE_BLOCKED_SENSITIVE_WORD = 21501,
  /**
   *  消息中敏感词已经被替换 （接收方可以收到被替换之后的消息）
   */
  RCIM_MESSAGE_REPLACED_SENSITIVE_WORD = 21502,
  /**
   * user id is not in room 操作的用户已经不在该房间了
   */
  RCIM_USER_NOT_IN_ROOM = 40001,
  /**
   * internal error 服务器内部错误
   */
  RCIM_SIGNAL_INTERNAL_ERROR = 40002,
  /**
   * server has no roominfo 没有该房间
   */
  RCIM_SERVER_HAS_NO_ROOM = 40003,
  /**
   * userId is Empty 用户id是空
   */
  RCIM_USERID_EMPTY = 40004,
  /**
   * limit error 房间人数超过限制
   */
  RCIM_ROOM_USER_LIMIT_ERROR = 40005,
  /**
   * param error 请求的参数错误
   */
  RCIM_PARAM_ERROR = 40006,
  /**
   * get token error token编解码错误
   */
  RCIM_TOKEN_ERROR = 40007,
  /**
   * db error
   */
  RCIM_DB_ERROR = 40008,
  /**
   * json error 解析json失败
   */
  RCIM_JSON_PARSED_ERROR = 40009,
  /**
   * not open voip error 用户没有开通音视频服务
   */
  RCIM_NOT_VOIP_PERMITS = 40010,
  /**
   * Room type is not created roomType error 加入房间的类型错误
   */
  RCIM_JOIN_ROOM_TYPE_ERROR = 40011,
  /**
   * The User have no auth 用户没有被授权（混合云）
   */
  RCIM_USER_HAS_NO_AUTH = 40012,
  /**
   * has no config MCU Address 没有配置混流地址
   */
  RCIM_NO_MCU_ADDRESS = 40015,
  /**
   * not allow video broadcast 不允许开启视频直播
   */
  RCIM_NOT_ALLOW__VIDEO_LIVING = 40016,
  /**
   * not allow audio broadcast 不允许开启音频直播
   */
  RCIM_NOT_ALLOW_AUDIO_LIVING = 40017,
  /**
   * get token failed 生成token失败
   */
  RCIM_TOKEN_GEN_FAILED = 40018,
  /**
   * user is blocked 用户被封禁
   */
  RCIM_USER_IS_BLOCKED = 40021,
  /**
   * invite room is not exist 邀请的房间不存在
   */
  RCIM_INVITED_ROOM_NOT_EXIST = 40022,
  /**
   * invite user is not exist 邀请的人不在房间内
   */
  RCIM_INVITED_USER_NOT_IN_ROOM = 40023,
  /**
   * invite is progress 正在邀请中，请勿重新邀请
   */
  RCIM_INVITE_IN_PROGRESS = 40024,
  /**
   * cancel invite but is not progress 取消邀请时,但是邀请信息不存在
   */
  RCIM_CANCEL_INVITE_NOT_IN_PROGRESS = 40025,
  /**
   * answer invite but is not progress 应答邀请时,邀请信息不存在
   */
  RCIM_ANSWER_INVITE_NOT_IN_PROGRESS = 40026,
  /**
   * answer invite timeout 应答邀请时, sessionID对不上
   */
  RCIM_ANSWER_INVITE_SESSION_TIMEOUT = 40027,
  /**
   * ping not progress ping时连麦信息不存在
   */
  RCIM_PING_NOT_IN_PROGRESS = 40028,

  /**
   * 观众加入直播房间超时
   */
  RCIM_JOIN_CHAT_ROOM_TIME_OUT = 50008,
} rc_message_error_code;

typedef enum rc_mentioned_type {
  RCIM_MENTIONED_NONE = 0,
  /*
   所有人
   */
  RCIM_MENTIONED_ALL = 1,
  /*
   部分指定用户
   */
  RCIM_MENTIONED_USERS = 2,
} rc_mentioned_type;

typedef enum rc_chatroom_user_order {
  RCIM_CHATROOM_USER_ORDER_ASC = 1,
  RCIM_CHATROOM_USER_ORDER_DESC = 2,
} rc_chatroom_user_order;

typedef enum rc_chatroom_messages_order {
  RCIM_CHATROOM_MESSAGES_ORDER_DESC = 0,
  RCIM_CHATROOM_MESSAGES_ORDER_ASC = 1,
} rc_chatroom_messages_order;
#ifdef __cplusplus
}
#endif

#endif  // IMLIB_API_RCIM_CONSTANTS_H_
