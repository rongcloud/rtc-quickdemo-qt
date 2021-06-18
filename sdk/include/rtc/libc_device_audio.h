/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

#ifndef RCRTCLIB_LIBC_DEVICE_AUDIO_H_
#define RCRTCLIB_LIBC_DEVICE_AUDIO_H_

#include "libc_rtc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 **************************************************
 * 音频输入收音器，音频输出扬声器，枚举和测试函数
 **************************************************
 */

/**
 * @brief 全局初始化音频设备麦克风和扬声器设备环境
 * 相关函数：
 * rcrtc_audio_device_uninit
 * rcim_init
 * rcrtc_init
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_audio_device_init(enum_rcrtc_audio_layer audio_layer);

/**
 * @brief 全局反初始化音频设备麦克风和扬声器设备环境
 * 相关函数：rcrtc_audio_device_init
 */
RCRTCLIB_API void rcrtc_audio_device_uninit();

/**
 * @brief 获取扬声器设备个数
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 *
 * @return 扬声器设备个数
 * - >=0：success
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_get_speaker_num();

/**
 * @brief 获取麦克风设备个数
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 *
 * @return 麦克风设备个数
 * - >= 0：success
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_get_microphone_num();

/**
 * @brief 获取扬声器设备名称
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_audio_device_get_speaker_name(uint32_t index,
                                    char name[MAX_DEVICE_NAME_SIZE]);
/**
 * @brief 获取麦克风设备名称
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t
rcrtc_audio_device_get_microphone_name(uint32_t index,
                                       char name[MAX_DEVICE_NAME_SIZE]);

/**
 * @brief 设定当前使用的扬声器
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * - 如当前在会议中（调用 rcrtc_enable_audio），须先调用 rcrtc_disable_audio
 * - 如当前在扬声器设备的检测（调用 rcrtc_audio_device_start_speaker_test），
 * 须先调用 rcrtc_audio_device_stop_microphone_test
 * - 如当前在麦克风设备的检测（调用 rcrtc_audio_device_start_microphone_test），
 * 须先调用 rcrtc_audio_device_stop_speaker_test
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_set_speaker_index(uint32_t index);

/**
 * @brief 设定当前使用的麦克风
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * - 如当前在会议中rcrtc_enable_audio，先调用 rcrtc_disable_audio。
 * - 如当前在扬声器设备的检测（调用 rcrtc_audio_device_start_speaker_test），
 * 须先调用 rcrtc_audio_device_stop_microphone_test，停止检测。
 * - 如当前在麦克风设备的检测 （调用
 * rcrtc_audio_device_start_microphone_test）， 须先调用
 * rcrtc_audio_device_stop_speaker_test，停止检测。
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_set_microphone_index(uint32_t index);

/**
 * @brief 设定当前使用扬声器设备的音量
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_speaker_index 先要调用
 *
 * @param vol                         范围[0-100]
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_set_speaker_volume(uint32_t vol);

/**
 * @brief 设定当前使用麦克风设备的音量
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_microphone_index 先要调用
 *
 * @param vol                         范围[0-100]
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_audio_device_set_microphone_volume(uint32_t vol);

/**
 * @brief 当前使用麦克风设备的检测开始
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_microphone_index 先要调用
 *
 * @param callback                      回调函数指针
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_device_start_microphone_test(
    fn_rcrtc_mic_test_callback callback,
    HANDLE context);

/**
 * @brief 当前使用麦克风设备的检测结束
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_microphone_index 先要调用
 * rcrtc_audio_device_start_microphone_test 先要调用
 *
 * @return
 * - 0：成功
 * - -1：失败
 */

RCRTCLIB_API
int32_t rcrtc_audio_device_stop_microphone_test();

/**
 * @brief 当前扬声器设备的检测开始
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_speaker_index 先要调用
 *
 * @param file_path                     pcm 采样率 48k 双声道 位深16 bits，
 * 全路径
 * @param callback                      回调函数指针
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_device_start_speaker_test(
    const char file_path[256],
    fn_rcrtc_spk_test_callback callback,
    HANDLE context);

/**
 * @brief 扬声器设备的检测结束
 * 相关函数：
 * rcrtc_audio_device_init 先要调用
 * rcrtc_audio_device_set_speaker_index 先要调用
 * rcrtc_audio_device_start_speaker_test 先要调用
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_audio_device_stop_speaker_test();

/*
 **************************************************
 * 扬声器和麦克风设备开启和关闭
 **************************************************
 */

/**
 * @brief 启用麦克风、扬声器设备
 * 相关函数：
 * rcrtc_audio_device_init 设备初始化函数先要调用
 * rcrtc_audio_device_set_speaker_index 先要调用
 * rcrtc_audio_device_set_microphone_index 先要调用
 *
 * @sa rcrtc_disable_audio
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_enable_audio();

/**
 * @brief 禁用麦克风、扬声器设备
 * @sa rcrtc_enable_audio
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_disable_audio();

/*
 **************************************************
 * 桌面采集本地声卡设备开启和关闭
 **************************************************
 */
#if defined(WIN32)
/**
 * @brief 启用系统扬声器录制
 * 相关函数：
 * rcrtc_audio_device_init 设备初始化函数先要调用
 *
 * @sa rcrtc_disable_system_audio
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_enable_system_audio();
/**
 * @brief 禁用系统扬声器录制
 * 相关函数：
 * rcrtc_audio_device_init 设备初始化函数先要调用
 *
 * @sa rcrtc_enable_system_audio
 *
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API int32_t rcrtc_disable_system_audio();
#endif

#ifdef __cplusplus
}
#endif
#endif
