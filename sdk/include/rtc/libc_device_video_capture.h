/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_DEVICE_VIDEO_CAPTURE_H_
#define RCRTCLIB_LIBC_DEVICE_VIDEO_CAPTURE_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ******************************************************
 * 摄像头视频采集输入设备信息相关函数
 ******************************************************
 */

/**
 * @brief 设置本地视频采集数据回调
 * @param cb                            回调函数指针
 * @param context                       上下文，通过
 * fn_rcrtc_video_data_callback 数据回调
 * @return int32_t
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_capture_set_cb(const fn_rcrtc_video_data_callback cb,
                                   HANDLE context);

/**
 * @brief 删除之前注册过的本地视频采集数据回调
 * @param cb                            需要删除的回调
 * fn_rcrtc_video_data_callback 数据回调
 */
RCRTCLIB_API void rcrtc_video_capture_remove_cb(
    const fn_rcrtc_video_data_callback cb);

/**
 * @brief 创建摄像头枚举句柄
 *
 * @return 摄像头枚举句柄
 * - not NULL：success
 * - NULL：failure
 */
RCRTCLIB_API HANDLE_DEVICE_INFO rcrtc_video_capture_create_device_info();

/**
 * @brief 销毁摄像头枚举句柄
 *
 * @param handle  摄像头枚举句柄
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_video_capture_destroy_device_info(HANDLE_DEVICE_INFO handle);

/**
 * @brief 获取可用摄像头个数
 *
 * @param  handle 摄像头枚举句柄
 * @return 可用摄像头个数
 */
RCRTCLIB_API uint32_t
rcrtc_video_capture_get_device_number(HANDLE_DEVICE_INFO handle);

/**
 * @brief 获取指定摄像头名字
 * device_index 获取参考 rcrtc_video_capture_get_device_number
 *
 * @param handle 摄像头枚举句柄
 * @param device_index                  摄像头在枚举句柄的索引值
 * @param device_name_utf8              摄像头名称字符串
 * @param device_name_length            摄像头名称字符串长度
 * @param device_unique_id_utf8         摄像头唯一标识字符串
 * @param device_unique_id_utf8_length  摄像头唯一标识字符串长度
 * @param product_unique_id_utf8        摄像头产品标识字符串
 * @param product_unique_id_utf8_length 摄像头产品标识字符串长度
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_video_capture_get_device_name(HANDLE_DEVICE_INFO handle,
                                    uint32_t device_index,
                                    char* device_name_utf8,
                                    uint32_t device_name_length,
                                    char* device_unique_id_utf8,
                                    uint32_t device_unique_id_utf8_length,
                                    char* product_unique_id_utf8,
                                    uint32_t product_unique_id_utf8_length);

/**
 * @brief 获取输出图像的旋转角度
 *
 * @param handle 摄像头枚举句柄
 * @param device_unique_id_utf8     摄像头唯一标识
 * @param orientation               图像旋转角度枚举指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_video_capture_get_orientation(HANDLE_DEVICE_INFO handle,
                                    const char* device_unique_id_utf8,
                                    enum_rcrtc_video_rotation* orientation);

/**
 * @brief 设置本地设备视频渲染窗口
 *
 * @param canvas  设置本地设备视频渲染窗口所需的参数
 * @return
 * - 0：成功
 * - -1：失败
 *
 */
RCRTCLIB_API int32_t
rcrtc_video_capture_attach_local_video(rcrtc_video_canvas_t* canvas);

/**
 * @brief 取消设置本地设备视频渲染窗口
 *
 * @param rc_view  取消设置本地设备视频渲染窗口所需的参数
 * @return
 * - 0：成功
 * - -1：失败
 *
 */
RCRTCLIB_API int32_t rcrtc_video_capture_dettach_local_video(RCView rc_view);

/*
 * *********************************************************
 * 摄像头视频采集输入使能函数
 * *********************************************************
 */

/**
 * @brief 启用指定的摄像头
 * device_index 获取参考 rcrtc_video_capture_get_device_number
 *
 * @param device_index              摄像头在枚举句柄中的索引值
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_enable_video(const uint32_t device_index);

/**
 * @brief 切换摄像头
 * device_index 获取参考 rcrtc_video_capture_get_device_number
 *
 * @param device_index              摄像头在枚举句柄中的索引值
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_switch_video(const uint32_t device_index);

/**
 *
 * @brief 禁用摄像头
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_disable_video();

/**
 * @brief 重新设置stream_handle对应视频设备的最大帧率
 *
 * @param stream_handle 要设置最大帧率的流句柄
 * @param max_fps		要设置的最大帧率
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_set_video_fps(HANDLE_STREAM stream_handle,
                                         enum_rcrtc_video_frame_rate max_fps);

/**
 * @brief 重新设置stream_handle对应视频设备的分辨率
 *
 * @param stream_handle 要设置分辨率的流句柄
 * @param max_fps		要设置的分辨率
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_set_video_resolution(HANDLE_STREAM stream_handle,
                           enum_rcrtc_video_resolution resolution);

#ifdef __cplusplus
}
#endif
#endif
