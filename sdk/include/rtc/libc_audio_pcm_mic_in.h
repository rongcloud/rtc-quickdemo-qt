/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_AUDIO_PCM_MIC_IN_H_
#define RCRTCLIB_EXTENSION_LIBC_AUDIO_PCM_MIC_IN_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief rcrtc引擎 创建麦克风采集句柄，全局唯一
 * 输入音频通道，通道个数 1。采样频率 8000，16000，32000，44100，48000。采样位深
 * 16
 *
 * @param handle         引擎句柄
 * @param channels       通道个数
 * @param sample_rate    采样频率
 * @param sample_bits    采样位深
 * @param tag            自定义音频流的tag标识,注意:这个tag不要带英语格式的下划线字符("_")
 * @return HANDLE_STREAM 调用成功返回引擎句柄，否则返回 NULL。
 */
RCRTCLIB_API HANDLE_STREAM
rcrtc_pcm_mic_in_create(HANDLE_RTC_ENGINE handle,
                        enum_rcrtc_channel channels,
                        enum_rcrtc_sample_rate sample_rate,
                        int32_t sample_bits,
                        const char* tag);

/**
 * @brief rcrtc 引擎 销毁麦克风采集句柄
 *
 * @param handle         麦克风采集句柄
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_pcm_mic_in_destroy(HANDLE_STREAM handle);

/**
 * @brief rcrtc 引擎 写入模拟麦克风输入的 pcm 声音数据，
 * 输入音频通道，通道个数 1，采样频率 【8000，16000，32000，44100，
 *  48000】，采样位深 16
 *
 * @param handle         麦克风采集句柄
 * @param data           pcm 数据
 * @param size           数据长度
 * @param time_ms        采样从设备采集到的时刻单位毫秒
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_pcm_mic_in_write(HANDLE_STREAM handle,
                               const uint8_t* data,
                               uint32_t size,
                               int64_t time_ms);

#ifdef __cplusplus
}

#endif

#endif
