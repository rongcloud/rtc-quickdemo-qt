/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_VIDEO_IMAGE_RENDER_H_
#define RCRTCLIB_EXTENSION_LIBC_VIDEO_IMAGE_RENDER_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置远端视频图像数据回调
 * @param stream                        流句柄
 * @param cb                            回调函数指针
 * @param context                       上下文，通过
 * fn_rcrtc_video_data_callback 回传
 * @return int32_t
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_image_set_cb(HANDLE_STREAM stream,
                                 fn_rcrtc_video_data_callback cb,
                                 HANDLE context);

#ifdef __cplusplus
}
#endif

#endif
