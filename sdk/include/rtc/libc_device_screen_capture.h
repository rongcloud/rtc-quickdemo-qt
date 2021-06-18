/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_DEVICE_SCREEN_CAPTURE_H_
#define RCRTCLIB_LIBC_DEVICE_SCREEN_CAPTURE_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *******************************************************************
 * 桌面和窗口采集输入信息相关函数
 *******************************************************************
 */

/**
 * @brief 获取当前的窗口列表
 *
 * @param window_list 存储窗口列表的 HANDLE_WINDOW* 数组
 * @param list_size 数组的最大长度
 * HANDLE_WINDOW* 窗口句柄数组，调用方需要维护句柄数组的内存和定义数组长度
 * @return
 * - 成功返回：数组中窗口列表的长度
 * - 失败返回：-1
 */
RCRTCLIB_API int32_t
rcrtc_screen_capture_get_window_list(HANDLE_WINDOW* window_list,
                                     int32_t list_size);

/**
 * @brief 获取当前的显示器列表
 *
 * @param monitor_list 存储显示器列表的 HANDLE_MONITOR* 数组
 * @param list_size 数组的最大长度
 * HANDLE_MONITOR* 显示器句柄数组，调用方需要维护句柄数组的内存和定义数组长度
 * @return
 * - 成功返回：数组中显示器数组的长度
 * - 失败返回：-1
 */
RCRTCLIB_API int32_t
rcrtc_screen_capture_get_monitor_list(HANDLE_MONITOR* window_list,
                                      int32_t list_size);

/**
 * @brief 获取指定窗口标题
 *
 * @param window_handle 窗口句柄
 *
 * @return
 * - 成功返回：窗口标题
 * - 失败返回：NULL
 */
RCRTCLIB_API const char* rcrtc_screen_capture_get_window_title(
    HANDLE_WINDOW window_handle);

/**
 * @brief 获取指定显示器标题
 *
 * @param monitor_handle 显示器句柄
 *
 * @return
 * - 成功返回：显示器标题
 * - 失败返回：NULL
 */
RCRTCLIB_API const char* rcrtc_screen_capture_get_monitor_title(
    HANDLE_MONITOR monitor_handle);

/**
 * @brief 创建全局唯一的创建屏幕采集的视频流，指定采集的窗口名字
  （窗口句柄由 rcrtc_screen_capturer_get_window_list 获取）
 *
 * @param window_handle 窗口句柄
 *
 * @return
 * - 成功返回：HANDLE_STREAM 句柄
 * - 失败返回：NULL
 */
RCRTCLIB_API HANDLE_STREAM
rcrtc_screen_capture_create_stream_by_window(HANDLE_WINDOW window_handle,
                                             const char* tag_name);

/**
 * @brief 创建全局唯一的屏幕采集的视频流，指定采集的显示器名字
 * (显示器句柄由 rcrtc_screen_capturer_get_monitor_list 获取）
 *
 * @param monitor_handle 显示器句柄
 *
 * @return
 * - 成功返回：HANDLE_STREAM 句柄
 * - 失败返回：NULL
 */
RCRTCLIB_API HANDLE_STREAM
rcrtc_screen_capture_create_stream_by_monitor(HANDLE_MONITOR monitor_handle,
                                              const char* tag_name);

/**
 * @brief 创建全局唯一的创建屏幕采集的视频流，指定采集的区域
 *
 * @param rect_x 区域的左上角 x 坐标
 * @param rect_y 区域的左上角 y 坐标
 * @param rect_w 区域的 宽
 * @param rect_h 区域的 高
 *
 * @return
 * - 成功返回：HANDLE_STREAM 句柄
 * - 失败返回：NULL
 */
RCRTCLIB_API HANDLE_STREAM
rcrtc_screen_capture_create_stream_by_rect(int32_t rect_x,
                                           int32_t rect_y,
                                           int32_t rect_w,
                                           int32_t rect_h,
                                           const char* tag_name);

/**
 * @brief 销毁屏幕采集的视频流
 *
 * @param stream 局唯一的屏幕采集的视频流句柄
 */
RCRTCLIB_API void rcrtc_screen_capture_destroy_stream(HANDLE_STREAM stream);

/**
 * @brief 设置需要在屏幕共享时过滤的窗口
 *
 * @param window_list 窗口句柄列表
 *
 * HANDLE_WINDOW* 窗口句柄数组，调用方需要维护句柄数组的内存和定义数组长度
 */
RCRTCLIB_API void rcrtc_screen_capture_set_exclude_window_list(
    HANDLE_WINDOW* window_list,
    int32_t list_size);

/**
 * @brief 开始屏幕采集
 * @return
 * - 成功返回：0
 * - 失败返回：-1
 */
RCRTCLIB_API int32_t rcrtc_screen_capture_start_capture();

/**
 * @brief 停止屏幕采集
 */
RCRTCLIB_API void rcrtc_screen_capture_stop_capture();

/**
 * @brief 设置是否在屏幕共享时采集鼠标位置
 */
RCRTCLIB_API void rcrtc_screen_capture_enable_capture_mouse(bool enable);

/**
 * @brief 开始屏幕采集
 * @return
 * - 采集鼠标返回：true
 * - 否则返回：false
 */
RCRTCLIB_API bool rcrtc_screen_capture_is_enable_capture_mouse();

/**
 * @brief 设置屏幕采集的帧率 fps
 */
RCRTCLIB_API void rcrtc_screen_capture_set_fps(enum_rcrtc_video_frame_rate fps);

/**
 * @brief 获取当前的帧率
 * @return
 * - 成功返回：实际的帧率
 */
RCRTCLIB_API enum_rcrtc_video_frame_rate rcrtc_screen_capture_get_fps();

/**
 * @brief 设置屏幕采集的分辨率
 */
RCRTCLIB_API void rcrtc_screen_capture_set_resolution(
    enum_rcrtc_screen_capture_resolution resolution);

/**
 * @brief 获取当前的分辨率
 * @return
 * - 成功返回：实际的分辨率
 */
RCRTCLIB_API enum_rcrtc_screen_capture_resolution
rcrtc_screen_capture_get_resolution();

#ifdef __cplusplus
}
#endif
#endif
