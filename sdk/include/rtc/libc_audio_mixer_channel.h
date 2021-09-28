/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_AUDIO_MIXER_CHANNEL_H_
#define RCRTCLIB_EXTENSION_LIBC_AUDIO_MIXER_CHANNEL_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 初始化全局自定义混音音频流环境初始化
 * 相关函数：
 * rcrtc_audio_mixer_channel_uninit
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_mixer_channel_init();

/** @brief 反初始化全局自定义混音音频流环境初始化
 * 相关函数：
 * rcrtc_audio_mixer_channel_init
 *
 * @return
 */
RCRTCLIB_API void rcrtc_audio_mixer_channel_uninit();

/**
 * @brief 创建发送自定义音频pcm数据流句柄
 * 相关函数：
 * rcrtc_audio_mixer_channel_init 先要调用全局调用一次
 *
 * @param channels 音频pcm数据的通道数
 * @param sample_rate  音频数据的采样率，目前支持8K、16K、48K
 * @param sample_bits  音频数据每采样的字节数，目前支持2字节(16bit)
 * @return
 * - not NULL：success
 * - NULL：failure
 */
RCRTCLIB_API HANDLE_AUDIO_MIXER_CHANNEL
rcrtc_audio_create_mixer_channel(enum_rcrtc_channel channels,
                                 enum_rcrtc_sample_rate sample_rate,
                                 int32_t sample_bits);

/**
 * @brief 销毁自定义音频数据流句柄
 *
 * @param handle_amc 要销毁的流句柄
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_audio_destroy_mixer_channel(HANDLE_AUDIO_MIXER_CHANNEL handle_amc);

/**
 * @brief
 * 发送10ms 字节长度自定义音频pcm数据,
 * 10ms
 * pcm数据的采样率,通道数和每采样的字节数由rcrtc_create_audio_mixer_channel所指定
 * (channels * (sample_bits / 8) * sample_rate) / 100
 *
 * @param handle_amc 要发送音频数据的流句柄
 * @param data     要发生的自定义音频数据指针
 * @param size     这块pcm数据的大小
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_audio_write_mixer_channel(HANDLE_AUDIO_MIXER_CHANNEL handle_amc,
                                const uint8_t* data,
                                uint32_t size);
#ifdef __cplusplus
}
#endif
#endif