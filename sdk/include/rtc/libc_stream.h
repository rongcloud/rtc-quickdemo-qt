/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_STREAM_H_
#define RCRTCLIB_LIBC_STREAM_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置流(direction 为 out，media_type 为
 * RCRTC_STREAM_MEDIA_VIDEO)码率配置 配置本地视频流资源码率
 *
 * @param handle_stream  流句柄
 * @param config         rcrtc_stream_bitrate_config_t 结构体指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_stream_set_bitrate_config(HANDLE_STREAM handle_stream,
                                rcrtc_stream_bitrate_config_t* config);

/**
 * @brief 获取流(direction 为 out，media_type 为
 * RCRTC_STREAM_MEDIA_VIDEO)码率配置 获取本地视频流资源码率
 * @param handle_stream  流句柄
 * @param config         rcrtc_stream_bitrate_config_t 结构体指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_stream_get_bitrate_config(HANDLE_STREAM handle_stream,
                                rcrtc_stream_bitrate_config_t* config);
/**
 * @brief 获取当前流 id
 * @param handle_stream  流句柄
 * @param stream_id      字符数组
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_stream_get_id(HANDLE_STREAM handle_stream,
                                         char stream_id[MAX_STRING_LEN]);

/**
 * @brief 获取当前流 tag，目前适用桌面采集流
 * @param handle_stream  流句柄
 * @param stream_tag     字符数组
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_stream_get_tag(HANDLE_STREAM handle_stream,
                                          char stream_tag[MAX_STRING_LEN]);

/**
 * @brief 获取当前流的资源 id
 * @param handle_stream  流句柄
 * @param resource_id    字符数组
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_stream_get_resource_id(HANDLE_STREAM handle_stream,
                             char resource_id[MAX_STRING_LEN]);

/**
 * @brief 获取当前流的媒体类型
 *
 * @param handle_stream  流句柄
 * @param type           结果地址指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_stream_get_media_type(HANDLE_STREAM handle_stream,
                            enum_rcrtc_stream_mediatype* type);

/**
 * @brief 获取当前流的方向
 *
 * @param handle_stream  流句柄
 * @param direction      结果地址指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_stream_get_direction(HANDLE_STREAM handle_stream,
                           enum_rcrtc_stream_direction* direction);

/**
 * @brief 获取媒体流是否已经发布
 * 对于本地媒体流：
 * - state：1 标识本地媒体流注册到服务器，可以被其他端订阅
 * - state：0 标识本地媒体流，不可以被其他端订阅
 *
 * 对于远端媒体流：
 * - state：1 远端媒体流可以被本地订阅
 * - state：0 远端流不可以订阅
 *
 * @param handle_stream  流句柄
 * @param state          结果地址指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_stream_get_state(HANDLE_STREAM handle_stream,
                                            int32_t* state);
/**
 * @brief 设置媒体流状态
 * 对于本地媒体流：mute 为 1 则不发送媒体资源（不影响采集和本地预览）
 * 对于远端媒体流：mute 为 1
 * 则不再解码播放或者渲染远端媒体流（但会正常接收远端媒体流）
 *
 * @param handle_stream  流句柄
 * @param mute           0 启用，非 0 禁用
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_stream_set_mute(HANDLE_STREAM handle_stream,
                                           int32_t mute);

/**
 * @brief 获取媒体流状态
 * 对于本地媒体流：mute 为 1 则不发送媒体资源（不影响采集和本地预览）
 * 对于远端媒体流：mute 为 1
 * 则不再解码播放或者渲染远端媒体流（但会正常接收远端媒体流）
 *
 * @param handle_stream  流句柄
 * @param mute           结果地址指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_stream_get_mute(HANDLE_STREAM handle_stream,
                                           int32_t* mute);

#ifdef __cplusplus
}
#endif

#endif
