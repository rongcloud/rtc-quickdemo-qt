/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_VIDEO_IMAGE_CAPTURER_H_
#define RCRTCLIB_EXTENSION_LIBC_VIDEO_IMAGE_CAPTURER_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建图像数据写入句柄
 *
 * @param handle          引擎句柄
 * @param video_type      视频格式类型
 * @param resolution      视频分辨率
 * @param frame_rate      视频帧率
 * @param tag             自定义视频流标识
 * @return HANDLE_STREAM
 * - 成功，返回值为创建的实例句柄
 * - 失败，返回 NULL
 */
RCRTCLIB_API
HANDLE_STREAM
rcrtc_video_create_image_capture(HANDLE_RTC_ENGINE handle,
                                 enum_rcrtc_video_type video_type,
                                 enum_rcrtc_video_resolution resolution,
                                 enum_rcrtc_video_frame_rate frame_rate,
                                 const char* tag);

/**
 * @brief 写入图像数据
 * @param handle          实例句柄
 * @param data            图像数据
 * @param len             图像数据长度
 * @param width           图像宽度
 * @param height          图像宽度
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_write_image_capture(HANDLE_STREAM handle,
                                        const void* data,
                                        const int32_t len,
                                        int32_t width,
                                        int32_t height);

/**
 * @brief 销毁图像数据写入句柄
 * @param handle          实例句柄
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_destroy_image_capture(HANDLE_STREAM handle);

#ifdef __cplusplus
}
#endif

#endif
