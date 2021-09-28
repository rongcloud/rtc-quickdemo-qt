/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_ENGINE_H_
#define RCRTCLIB_LIBC_ENGINE_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化 SDK，设置基本参数，此接口是全局接口，应在连接之前调用
 * @param imlib_engine   初始化 rcim sdk 返回的 rcim 引擎句柄
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_init(HANDLE_IM_ENGINE imlib_engine);

/**
 * @brief 反初始化
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_uninit();

/**
 * @brief 获取HANDLE_RTC_ENGINE句柄
 *
 * rcrtc_get_engine
 * @return 成功获取引擎时，返回的句柄非空，否则返回 NULL。
 */
RCRTCLIB_API HANDLE_RTC_ENGINE rcrtc_get_engine();

/**
 * @brief 设置媒体服务器地址
 *
 * @param server_url       媒体服务器地址
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_set_media_server_url(const char* server_url);

/**
 * @brief 设置配置参数
 *
 * @param config 引擎配置
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_set_config(rcrtc_config_t* config);

/**
 * @brief 设置 rcrtc engine 错误回调函数
 *
 * @param callback 回调函数
 * @param context  上下文
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_set_engine_callback(fn_rcrtc_general_callback callback, HANDLE context);

/**
 * @brief 设置本地视频渲染窗口
 *
 * @param canvas  设置本地视频渲染窗口所需的参数
 * @return
 * - 0：成功
 * - -1：失败
 *
 */
RCRTCLIB_API int32_t rcrtc_setup_local_video(rcrtc_video_canvas_t* canvas);

/**
 * @brief 订阅流，分别订阅大流、小流
 * 一个流的句柄只能存入大流和小流其中一个数组，不能两个数组都包含此流的句柄
 *
 * @param room_id       房间 id
 * @param streams       大流的句柄数组，订阅这些流
 * @param tiny_streams  小流的句柄数组，订阅这些流
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_subscribe_streams(const char* room_id,
                        HANDLE_STREAM streams[MAX_STREAM_COUNT],
                        HANDLE_STREAM tiny_streams[MAX_STREAM_COUNT],
                        fn_rcrtc_general_callback callback,
                        HANDLE context);

/**
 * @brief 取消订阅流
 *
 * @param room_id         房间 id
 * @param streams         流句柄数组，取消这些流的订阅
 * @param callback        取消订阅回调函数指针
 * @param context         用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_unsubscribe_streams(const char* room_id,
                          HANDLE_STREAM streams[MAX_STREAM_COUNT],
                          fn_rcrtc_general_callback callback,
                          HANDLE context);

/**
 * @brief 订阅流，分别订阅大流、小流
 * 一个流的句柄只能存入大流和小流其中一个数组，不能两个数组都包含此流的句柄
 *
 * @param room_id       房间 id
 * @param streams       大流的句柄数组，订阅这些流
 * @param tiny_streams  小流的句柄数组，订阅这些流
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_subscribe_stream(const char* room_id,
                       HANDLE_STREAM streams[MAX_STREAM_COUNT],
                       HANDLE_STREAM tiny_streams[MAX_STREAM_COUNT],
                       fn_rcrtc_stream_callback callback,
                       HANDLE context);

/**
 * @brief 取消订阅流
 *
 * @param room_id         房间 id
 * @param streams         流句柄数组，取消这些流的订阅
 * @param callback        取消订阅回调函数指针
 * @param context         用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_unsubscribe_stream(const char* room_id,
                         HANDLE_STREAM streams[MAX_STREAM_COUNT],
                         fn_rcrtc_stream_callback callback,
                         HANDLE context);

/**
 * @brief 获取默认的视频流
 *
 * @return 成功获取视频流时，返回的句柄非空，否则返回 NULL。
 */
RCRTCLIB_API HANDLE_STREAM rcrtc_get_default_video_stream();

/**
 * @brief 获取默认的音频流
 *
 * @return 成功获取音频流时，返回的句柄非空，否则返回 NULL。
 */
RCRTCLIB_API HANDLE_STREAM rcrtc_get_default_audio_stream();

/**
 * @brief 设置默认视频流分辨率，帧率，码率
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_default_video_stream_set_config(
    rcrtc_video_stream_config_t* video_config);

/**
 * @brief 获取默认视频流分辨率，帧率，码率
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_default_video_stream_get_config(
    rcrtc_video_stream_config_t* video_config);

/**
 * @brief 设定音视频通道质量回调
 *
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_set_user_quality_callback(fn_rcrtc_user_quality_callback callback,
                                HANDLE context);

/**
 * @brief 设定音频音量大小通知回调
 *
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_set_user_audio_energy_callback(
    fn_rcrtc_user_audio_energy_callback callback,
    HANDLE context);
/**
 * @brief 发布流
 *
 * @param callback  发布流的回调函数指针
 * @param context   用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_publish_default_streams(fn_rcrtc_general_callback callback,
                              HANDLE context);

/**
 * @brief 取消发布流
 *
 * @param room_id  房间 id
 * @param callback 回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_unpublish_default_streams(fn_rcrtc_general_callback callback,
                                HANDLE context);

/**
 * @brief 发布自定义流
 *
 * @param streams   用户创建的本地自定义流
 * @param callback  发布流的回调函数指针
 * @param context   用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_publish_streams(HANDLE_STREAM streams[MAX_STREAM_COUNT],
                              fn_rcrtc_general_callback callback,
                              HANDLE context);
/**
 * @brief 取消发布自定义流
 *
 * @param streams  用户创建的本地自定义流
 * @param callback 回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_unpublish_streams(HANDLE_STREAM streams[MAX_STREAM_COUNT],
                                fn_rcrtc_general_callback callback,
                                HANDLE context);

/**
 * @brief 发布流
 *
 * @param callback  发布流的回调函数指针
 * @param context   用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_publish_default_stream(fn_rcrtc_stream_callback callback, HANDLE context);

/**
 * @brief 取消发布流
 *
 * @param room_id  房间 id
 * @param callback 回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_unpublish_default_stream(fn_rcrtc_stream_callback callback,
                               HANDLE context);

/**
 * @brief 发布自定义流
 *
 * @param streams   用户创建的本地自定义流
 * @param callback  发布流的回调函数指针
 * @param context   用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_publish_stream(HANDLE_STREAM streams[MAX_STREAM_COUNT],
                             fn_rcrtc_stream_callback callback,
                             HANDLE context);
/**
 * @brief 取消发布自定义流
 *
 * @param streams  用户创建的本地自定义流
 * @param callback 回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_unpublish_stream(HANDLE_STREAM streams[MAX_STREAM_COUNT],
                               fn_rcrtc_stream_callback callback,
                               HANDLE context);

/**
 * @brief 加入房间
 *
 * @param room_id 房间 id 长度 64 个字符，
 * 可包含：`A-Z`、`a-z`、`0-9`、`+`、`=`、`-`、`_`
 * @param config  加入房间的参数配置，指明房间类型和直播角色等参数信息
 * @param callback 回调函数指针
 * @param context 用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_join_room(const char* room_id,
                                     rcrtc_room_config_t config,
                                     fn_rcrtc_join_room_callback callback,
                                     HANDLE context);

/**
 * @brief 离开当前房间
 *
 * @param room_id   房间 id
 * @param callback  离开房间结果回调函数
 * @param context   上下文，通过 \ref fn_rcrtc_general_callback 回传
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_leave_room(const char* room_id,
                                      fn_rcrtc_general_callback callback,
                                      HANDLE context);

/**
 * @brief 切换观众 / 主播角色
 *
 * @param room_id 房间 id
 * @param role 要转换到的直播角色
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_switch_role(const char* room_id,
                                       enum_rcrtc_live_role role);

/**
 * @brief 获取所有远端用户 id
 *
 * @param room_id         房间 id
 * @param remote_users    远端用户 id 数组结果返回
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_room_get_remote_users(
    const char* room_id,
    char remote_users[MAX_REMOTE_USER_COUNT][MAX_STRING_LEN]);

/**
 * @brief 加入房间后房间成员的状态变化
 *
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数，用于回调函数 \ref
 * rcrtc_room_event_callback
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_set_room_event_callback(fn_rcrtc_room_event_callback callback,
                              HANDLE context);

/**
 * @brief 加入房间成功后，房间内用户的流使能状态变化通知
 *
 * @param callback 回调函数指针
 * @param context  用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 *
 * @ref：fn_rcrtc_join_room_callback
 */
RCRTCLIB_API int32_t
rcrtc_set_remote_user_stream_callback(fn_rcrtc_remote_stream_callback callback,
                                      HANDLE context);

/**
 * @brief 渲染远端视频流到指定 canvas
 *
 * @param handle_stream  远端流句柄
 * @param canvas  流渲染到的窗口句柄、用户 id 等选项
 * @return
 * - 0：成功
 * - -1：失败
 *
 */
RCRTCLIB_API int32_t rcrtc_setup_video_stream(HANDLE_STREAM handle_stream,
                                              rcrtc_video_canvas_t* canvas);

/**
 * @brief 注册视频编码回调函数
 *
 * @param callback      回调函数指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_register_encoded_video_frame_callback(
    fn_rcrtc_encoded_video_frame_callback callback);

/**
 * @brief 注册获取远端已混音的PCM音频数据的回调函数
 *
 * @param callback      回调函数指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_register_remote_pcm_data_callback(rcrtc_pcm_audio_data_cb_func callback);

/**
 * @brief 注册获取本地PCM音频数据的回调函数
 *
 * @param callback      回调函数指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_register_local_pcm_data_callback(rcrtc_pcm_audio_data_cb_func callback);

/**
 * @brief 获取当前rtc版本号
 *
 * @param version      接收版本号的缓冲区
 * @param version_size 接收版本号缓冲区的长度
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_get_version(char* version, uint32_t version_size);

/**
 * @brief 获取当前通话的唯一标识。此sessionID会在调用
          ::rcrtc_join_room 接口成功后，由服务器返回。
 * 每加入一次房间，即使两次房间号一致，此sessionID也不同。
 *
 * @param room_id       房间 id
 * @param session_id    结果返回
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_room_get_session_id(const char* room_id,
                                               char session_id[MAX_STRING_LEN]);

/**
 * @brief 直播设置合流布局
 *
 * @param room_id       房间 id
 * @param layout       合流布局的json字符串
 * @param callback      回调函数指针
 * @param context       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_set_mix_stream_config(const char* room_id,
                            const char* config,
                            fn_rcrtc_general_json_callback callback,
                            HANDLE context);

#ifdef __cplusplus
}
#endif

#endif
