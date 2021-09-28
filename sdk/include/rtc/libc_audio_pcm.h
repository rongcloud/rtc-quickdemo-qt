/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_AUDIO_PCM_H_
#define RCRTCLIB_EXTENSION_LIBC_AUDIO_PCM_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief rcrtc 引擎获取设置回声消除，降噪，语音检测 此接口是全局接口
 *
 *
 * @param handle         引擎句柄
 * @param aec            >0 启用回音消除功能，0 关闭
 * @param ns             >0 启用降噪功能，0 关闭
 * @param vad            >0 启用语音检测功能，0 关闭
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_get_process_info(HANDLE_RTC_ENGINE handle,
                                     int32_t* aec,
                                     int32_t* ns,
                                     int32_t* vad);

/**
 * @brief rcrtc引擎 回声消除，降噪，语音检测 此接口是全局接口，在 sdk
 * 初始化后设置一直有效
 *
 * @param handle         引擎句柄
 * @param aec            >0 启用回音消除功能，0 关闭
 * @param ns             >0 启用降噪功能，0 关闭
 * @param vad            >0 启用语音检测功能，0 关闭
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_set_process_info(HANDLE_RTC_ENGINE handle,
                                     int32_t aec,
                                     int32_t ns,
                                     int32_t vad);
/**
 * @brief rcrtc引擎 回声消除扬声器外放到再次被麦克风录入时间时长间隔
 * 此接口是全局接口，在sdk初始化后设置一直有效
 *
 * @param handle         引擎句柄
 * @param time_ms        单位毫秒
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_get_input_record_delay(HANDLE_RTC_ENGINE handle,
                                           int32_t* time_ms);

/**
 * @brief rcrtc引擎 回声消除扬声器外放到再次被麦克风录入时间时长间隔
 * 此接口是全局接口，在sdk初始化后设置一直有效
 *
 * @param handle         引擎句柄
 * @param time_ms        单位毫秒
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_set_input_record_delay(HANDLE_RTC_ENGINE handle,
                                           int32_t time_ms);

/**
 * @brief rcrtc引擎 设置输出音频的pcm属性，
 * 输出音频通道，通道个数 【1，2】，采样频率
 * 【8000，16000，32000，44100，48000】，采样位深 16
 *
 * @param handle         引擎句柄
 * @param channels       通道个数
 * @param sample_rate    采样频率
 * @param sample_bits    采样位深
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_pcm_speaker_out_set_info(HANDLE_RTC_ENGINE handle,
                                       enum_rcrtc_channel channels,
                                       enum_rcrtc_sample_rate sample_rate,
                                       int32_t sample_bits);
/**
 * @brief rcrtc引擎 设置声音处理完毕后的回调函数
 *
 * @param handle    引擎句柄
 * @param cb        声音处理后的回调函数指针
 * @param context   上下文
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_pcm_speaker_out_register_callback(
    HANDLE_RTC_ENGINE handle,
    fn_rcrtc_pcm_speaker_out_data_callback cb,
    HANDLE context);

/**
 * @brief rcrtc引擎 取消设置声音处理完毕后的回调函数
 *
 * @param handle    引擎句柄
 * @param cb        声音处理后的回调函数指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_pcm_speaker_out_unregister_callback(
    HANDLE_RTC_ENGINE handle,
    fn_rcrtc_pcm_speaker_out_data_callback cb);

#ifdef __cplusplus
}

#endif
#endif
