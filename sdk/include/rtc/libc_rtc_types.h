/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_LIBC_RTC_TYPES_H_
#define RCRTCLIB_LIBC_RTC_TYPES_H_

#include "libc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DEVICE_NAME_SIZE 128
#define MAX_REMOTE_USER_COUNT 256
#define MAX_STRING_LEN 256
#define MAX_STREAM_COUNT 64

#define MAX_MIC_VOL 100
#define MIN_MIC_VOL 0
#define MAX_SPK_VOL 100
#define MIN_SPK_VOLL 0

/**
 * 窗口句柄
 */
typedef void* RCView;
/**
 * 设备枚举句柄
 */
typedef void* HANDLE_DEVICE_INFO;
/**
 * RTC 引擎句柄
 */
typedef void* HANDLE_RTC_ENGINE;
/**
 * 音视频流句柄
 */
typedef void* HANDLE_STREAM;
/**
 * 音视频自定义流句柄
 */
typedef void* HANDLE_AUDIO_MIXER_CHANNEL;
/**
 * 视频渲染句柄
 */
typedef void* HANDLE_VIDEO_RENDER;

/**
 * 屏幕共享窗口句柄
 */
typedef void* HANDLE_WINDOW;
typedef void** HANDLE_WINDOW_LIST;

/**
 * 屏幕共享显示器句柄
 */
typedef void* HANDLE_MONITOR;
typedef void** HANDLE_MONITOR_LIST;

/**
 * 音视频错误码定义
 * 服务器返回错误以 4 开头，后两位是业务代码，最后两位是错误码 4XXXX，如 400XX
 * 基础连接部分 本地返回错误以 5 开头，后两位是业务代码，最后两位是错误码
 * 5XXXX，如 500XX 初始化基础连接部分
 */
typedef enum enum_rcrtc_code {
  /**
   * 错误
   */
  RCRTC_ERROR = -1,
  /**
   * 成功
   */
  RCRTC_SUCCESS = 0,
  /**
   * 初始化失败，信令服务（IM Server）未连接
   */
  RCRTC_CODE_SIGNAL_SERVER_NOT_CONNECT = 50000,
  /*
  参数错误
   */
  RCRTC_CODE_PARAMETER_ERROR = 50001,
  /**
   * 加入相同房间错误，表示用户在客户端重复加入相同的房间
   */
  RCRTC_CODE_JOIN_SAME_ROOM = 50002,
  /**
   * 不在房间中
   */
  RCRTC_CODE_NOT_IN_ROOM = 50003,
  /**
   * 请检查是否开通音视频服务
   */
  RCRTC_CODE_ENGINE_ERROR = 50004,
  /**
   *  RTC token为空，请查看是否还在房间内或者房间是否销毁
   */
  RCRTC_CODE_TOKEN_IS_NULL = 50006,

  /**
   * RTC 加入直播房间超时
   */
  RCRTC_JOIN_CHAT_ROOM_TIMEOUT = 50008,
  /**
   * HTTP 请求超时
   */
  RCRTC_CODE_HTTP_TIMEOUT_ERROR = 50010,
  /**
   * HTTP 响应错误（含 500，404，405 等错误）
   */
  RCRTC_CODE_HTTP_RESPONSE_ERROR = 50011,
  /**
   * HTTP 请求错误（含网络不可达，请求未能为能正常发出）
   */
  RCRTC_CODE_HTTP_REQUEST_ERROR = 50012,
  /**
   * 发布重复资源
   */
  RCRTC_CODE_PUBLISH_DUPLICATE_RESOURCES = 50020,
  /**
   * 初步会话协商错误，没有消息的音视频参数
   */
  RCRTC_CODE_SESSION_DEGOTIATE_OFFER_ERROR = 50021,
  /**
   * 会话协商错误，协商数据不匹配或者其他问题
   */
  RCRTC_CODE_SESSION_DEGOTIATE_SET_REMOTE_ERROR = 50022,
  /**
   * 发布的流的个数已经到达上限
   */
  RCRTC_CODE_PUBLISH_STREAM_HAS_REACHED_MAX_COUNT = 50023,
  /**
   * 取消发布不存在的资源
   */
  RCRTC_CODE_UNPUBLISH_NOT_EXIST_STREAM = 50024,
  /**
   * 订阅不存在的音视频资源
   */
  RCRTC_CODE_SUBSCRIBE_NOT_EXIST_RESOURCES = 50030,
  /**
   * 资源重复订阅
   */
  RCRTC_CODE_SUBSCRIBE_DUPLICATE_RESOURCES = 50031,
  /**
   * 取消订阅不存在的音视频资源
   */
  RCRTC_CODE_UNSUBSCRIBE_NOT_EXIST_RESOURCE = 50032,
  /**
   * SDK 内部业务逻辑错误码
   */
  RCRTC_CODE_SDK_INTERNAL_ERROR = 50071,
  /**
   * cdn 地址配置数量到达上限（最大为10个）
   */
  RCRTC_CODE_CDN_COUNT_REACH_LIMIT = 50080,
} enum_rcrtc_code;

/** 声道类型 */
typedef enum enum_rcrtc_channel {
  // 单声道
  RCRTC_CHANNEL_MONO = 0x1,
  // 双声道
  RCRTC_CHANNEL_STEREO = 0x2,
} enum_rcrtc_channel;

/** 声音采样率 */
typedef enum enum_rcrtc_sample_rate {
  RCRTC_SAMPLE_RATE_8000HZ = 8000,
  RCRTC_SAMPLE_RATE_16000HZ = 16000,
  RCRTC_SAMPLE_RATE_32000HZ = 32000,
  RCRTC_SAMPLE_RATE_44100HZ = 44100,
  RCRTC_SAMPLE_RATE_48000HZ = 48000,
} enum_rcrtc_sample_rate;

/** 音频设备平台类型 */
typedef enum enum_rcrtc_audio_layer {
  RCRTC_AUDIO_LAYER_PLATFORM_DEFAULT = 0,
  RCRTC_AUDIO_LAYER_WINDOWS_AUDIO = 1,
  RCRTC_AUDIO_LAYER_LINUX_AUDIO = 2,
  RCRTC_AUDIO_LAYER_MAC_AUDIO = 3,
} enum_rcrtc_audio_layer;

/** 图像类型枚举 **/
typedef enum enum_rcrtc_video_type {
  RCRTC_VIDEO_PARAM_UNKNOWN = 0,
  RCRTC_VIDEO_PARAM_I420 = 1,
  RCRTC_VIDEO_PARAM_H264 = 12,
} enum_rcrtc_video_type;

/**
 * 视频流分辨率
 */
typedef enum enum_rcrtc_video_resolution {
  RCRTC_VIDEO_176_144,
  RCRTC_VIDEO_180_180,
  RCRTC_VIDEO_256_144,
  RCRTC_VIDEO_240_180,
  RCRTC_VIDEO_320_180,
  RCRTC_VIDEO_240_240,
  RCRTC_VIDEO_320_240,
  RCRTC_VIDEO_360_360,
  RCRTC_VIDEO_480_360,
  RCRTC_VIDEO_640_360,
  RCRTC_VIDEO_480_480,
  RCRTC_VIDEO_640_480,
  RCRTC_VIDEO_720_480,
  RCRTC_VIDEO_848_480,
  RCRTC_VIDEO_960_720,
  RCRTC_VIDEO_1280_720,
  RCRTC_VIDEO_1920_1080,
} enum_rcrtc_video_resolution;

/**
 * 屏幕共享流分辨率
 */
typedef enum enum_rcrtc_screen_capture_resolution {
  RCRTC_SCREEN_CAPTURE_720P = RCRTC_VIDEO_1280_720,
  RCRTC_SCREEN_CAPTURE_1080P = RCRTC_VIDEO_1920_1080,
} enum_rcrtc_screen_capture_resolution;

/**
 * 视频流帧率
 */
typedef enum enum_rcrtc_video_frame_rate {
  RCRTC_VIDEO_FPS_10,
  RCRTC_VIDEO_FPS_15,
  RCRTC_VIDEO_FPS_24,
  RCRTC_VIDEO_FPS_30,
} enum_rcrtc_video_frame_rate;

/** 图像格式枚举 **/
typedef enum enum_rcrtc_video_capture_type {
  RTC_VIDEO_TYPE_UNKNOWN = 0,
  RTC_VIDEO_TYPE_I420 = 1,
  RTC_VIDEO_TYPE_IYUV = 2,
  RTC_VIDEO_TYPE_RGB24 = 3,
  RTC_VIDEO_TYPE_ABGR = 4,
  RTC_VIDEO_TYPE_ARGB = 5,
  RTC_VIDEO_TYPE_ARGB4444 = 6,
  RTC_VIDEO_TYPE_RGB565 = 7,
  RTC_VIDEO_TYPE_ARGB1555 = 8,
  RTC_VIDEO_TYPE_YUY2 = 9,
  RTC_VIDEO_TYPE_YV12 = 10,
  RTC_VIDEO_TYPE_UYVY = 11,
  RTC_VIDEO_TYPE_MJPEG = 12,
  RTC_VIDEO_TYPE_NV21 = 13,
  RTC_VIDEO_TYPE_NV12 = 14,
  RTC_VIDEO_TYPE_BGRA = 15,
} enum_rcrtc_video_capture_type;

/** 图像旋转角度枚举 **/
typedef enum enum_rcrtc_video_rotation {
  RTC_VIDEO_ROTATION_0 = 0,
  RTC_VIDEO_ROTATION_90 = 90,
  RTC_VIDEO_ROTATION_180 = 180,
  RTC_VIDEO_ROTATION_270 = 270
} enum_rcrtc_video_rotation;

/**
 * @brief 图像属性
 */
typedef struct rcrtc_video_capture_capability_t {
  // 图像宽
  int32_t width;
  // 图像高
  int32_t height;
  // 图像输出最大帧率
  int32_t max_fps;
  // 图像格式
  enum_rcrtc_video_capture_type video_type;
  bool interlaced;
} rcrtc_video_capture_capability_t;

/**
 * stream 通道类型
 */
typedef enum enum_rcrtc_stream_mediatype {
  RCRTC_STREAM_MEDIA_UNKNOWN = -1,
  RCRTC_STREAM_MEDIA_AUDIO,
  RCRTC_STREAM_MEDIA_VIDEO,
  RCRTC_STREAM_MEDIA_DATA,
} enum_rcrtc_stream_mediatype;

/**
 * steam 方向类型
 */
typedef enum enum_rcrtc_stream_direction {
  RCRTC_STREAM_DIRECTION_UNKNOWN = -1,
  RCRTC_STREAM_DIRECTION_IN,
  RCRTC_STREAM_DIRECTION_OUT,
} enum_rcrtc_stream_direction;

/**
 * stream 码率设置 单位kbps
 * min_bitrate_kpbs < start_bitrate_kbps < max_bitrate_kbps
 */
typedef struct rcrtc_stream_bitrate_config_t {
  /**
   * 最小码率 单位kbps
   */
  int32_t min_bitrate_kbps;
  /**
   * 最大码率 单位kbps
   */
  int32_t max_bitrate_kbps;
  /**
   * 起始码率 单位kbps
   */
  int32_t start_bitrate_kbps;
} rcrtc_stream_bitrate_config_t;

typedef struct rcrtc_config_t {
  /**
   * 开启数据传输加密功能
   * 打开此功能会严重影响客户端和服务端处理性能
   * 默认 false 不使用， true 使用
   */
  bool enable_srtp;
  /**
   * 本地端口最起始值
   * 0 系统自动使用本地端口
   */
  int32_t min_port;
  /**
   * min_port 端口，端口范围值 【min_port， min_port+port_range_len】
   */
  int32_t port_range_len;

  /**
   *  是否启用视频小流
   *  true 启用，false 禁用，默认启用
   */
  bool enable_tiny_stream;

  /**
   * 音频设备平台类型
   */
  enum_rcrtc_audio_layer audio_layer;
} rcrtc_config_t;

typedef enum enum_rcrtc_video_fill_mode {
  /**
   * 图像长边填满屏幕，短边区域会被填充黑色
   */
  RCRTC_VIDEO_FILL_MODE_STRETCH_FIT = 0,

  /**
   * 图像铺满屏幕，超出显示视窗的视频部分将被裁剪
   */
  RCRTC_VIDEO_FILL_MODE_STRETCH_FILL = 1,
} enum_rcrtc_video_fill_mode;

/**
 * 视频渲染用到的配置参数项
 */
typedef struct rcrtc_video_canvas_t {
  RCView view;                                 // 窗口句柄
  char uid[MAX_STRING_LEN];                    // 用户 id
  bool video_mirror;                           // 是否镜像显示
  enum_rcrtc_video_fill_mode video_fill_mode;  // 图像显示的填充模式
} rcrtc_video_canvas_t;

typedef struct rcrtc_value_changed_t {
  void* old_value;
  void* new_value;
} rcrtc_value_changed_t;

typedef struct rcrtc_room_error_t {
  char* room_id;
  int32_t error_code;
  char* detail_msg;
} rcrtc_room_error_t;

typedef enum enum_rcrtc_quality {
  RCRTC_QUALITY_UNKNOWN = -1,
  RCRTC_QUALITY_BAD_VERY,
  RCRTC_QUALITY_BAD,
  RCRTC_QUALITY_POOR,
  RCRTC_QUALITY_GOOD,
  RCRTC_QUALITY_GOOD_VERY,
} enum_rcrtc_quality;
/**
 * 用户音视频通道质量
 */
typedef struct rcrtc_quality_t {
  /*
   * 用户 id
   */
  char* user_id;
  /*
   * quality
   */
  enum_rcrtc_quality quality;
} rcrtc_quality_t;

/**
 * 远端用户会议中音频分贝大小
 */
typedef struct rcrtc_out_vol_t {
  /*
   * 用户 id
   */
  char* user_id;
  /*
   * 【0，9】
   */
  int32_t energy;
} rcrtc_out_vol_t;

/**
 * 设置加入房间时音视频使用模式
 */
typedef enum enum_rcrtc_room {
  /**
   * 普通音视频类型
   */
  RCRTC_ROOM_MEETING = 0,
  /**
   * 直播类型
   */
  RCRTC_ROOM_LIVE = 2,
} enum_rcrtc_room;

/**
 * 直播类型
 */
typedef enum enum_rcrtc_live_type {
  /**
   * 当前直播为音视频直播
   */
  RCRTC_LIVE_AUDIO_VIDEO = 0,

  /**
   * 当前直播为仅音频直播
   */
  RCRTC_LIVE_AUDIO = 1,
} enum_rcrtc_live_type;

/**
 * 房间类型
 */
typedef enum enum_rcrtc_room_type {
  // 会议
  RCRTC_ROOM_TYPE_MEETING = (RCRTC_ROOM_MEETING << 8 | RCRTC_LIVE_AUDIO_VIDEO),
  // 直播音视频
  RCRTC_ROOM_TYPE_AUDIO_VIDEO = (RCRTC_ROOM_LIVE << 8 | RCRTC_LIVE_AUDIO_VIDEO),
  // 直播音频
  RCRTC_ROOM_TYPE_AUDIO = (RCRTC_ROOM_LIVE << 8 | RCRTC_LIVE_AUDIO),
} enum_rcrtc_room_type;

/**
 * 直播角色
 */
typedef enum enum_rcrtc_live_role {
  RCRTC_LIVE_ROLE_ANCHOR = 1,    // 主播
  RCRTC_LIVE_ROLE_AUDIENCE = 2,  // 观众
} enum_rcrtc_live_role;

/**
 * 要加入的房间的配置信息
 */
typedef struct rcrtc_room_config_t {
  enum_rcrtc_room_type room_type;
  enum_rcrtc_live_role live_role;
} rcrtc_room_config_t;

typedef enum enum_rcrtc_stream_event {
  /**
   * 对端用户开启视频流
   */
  RTC_STREM_EVENT_REMOTE_VIDEO_ENABLE,
  /**
   * 对端用户禁止视频流
   */
  RTC_STREM_EVENT_REMOTE_VIDEO_DISABLE,
  /**
   * 对端用户开启音频流
   */
  RTC_STREM_EVENT_REMOTE_AUDIO_ENABLE,
  /**
   * 对端用户禁用音频流
   */
  RTC_STREM_EVENT_REMOTE_AUDIO_DISABLE,
  /**
   * @Deprecated
   * 对端用户音频大小变化
   */
  RTC_STREM_EVENT_REMOTE_AUDIO_VOL_CHANGE,
} enum_rcrtc_stream_event;

typedef enum enum_rcrtc_room_event {
  /**
   *对端用户加入room
   */
  RTC_ROOM_EVENT_REMOTE_USER_JOINED,
  /**
   * 对端用户发布流地址可用
   */
  RTC_ROOM_EVENT_REMOTE_USER_STREAM_PUBLISHED,
  /**
   * 对端用户发布流地址失效
   * 事件参数 event_param 是 rcrtc_stream_info_t* 类型，
   * 包含取消发布流的信息。
   */
  RTC_ROOM_EVENT_REMOTE_USER_STREAM_UNPUBLISHED,
  /**
   * 对端用户离开room
   */
  RTC_ROOM_EVENT_REMOTE_USER_LEFT,
  /**
   *  对端用户第一帧视频。事件参数 event_param 表示视频流的 tag 值，char* 类型。
   */

  RTC_ROOM_EVENT_FIRST_REMOTE_VIDEO_FRAME,
  /**
   * 直播房间角色切换的事件回调。事件参数 event_param 是 rcrtc_value_changed_t*
   * 类型。 包含角色转换前后的值。
   */
  RTC_ROOM_EVENT_SWITCH_ROLE,

  /**
   * 直播房间角色切换失败事件回调。事件参数 event_param 是 rcrtc_room_error_t*
   * 类型，说明具体错误。
   */
  RTC_ROOM_EVENT_SWITCH_ROLE_ERROR,
} enum_rcrtc_room_event;

/**
 * 视频流分辨率，帧率，码率设置
 */
typedef struct rcrtc_video_stream_config_t {
  /**
   * 大流分辨率配置
   */
  enum_rcrtc_video_resolution video_resolution_big;
  /**
   * 小流分辨率配置
   */
  enum_rcrtc_video_resolution video_resolution_small;
  /**
   * 大流帧率配置，小流使用默认值 15 帧
   */
  enum_rcrtc_video_frame_rate video_frame_rate;
  /**
   * 视频类型
   */
  enum_rcrtc_video_capture_type video_type;
  /**
   * 码率配置
   */
  rcrtc_stream_bitrate_config_t video_bitrate;
} rcrtc_video_stream_config_t;

/**
 * @brief 通用回调函数定义
 * @param code                          结果码
 * @param context                       用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_general_callback)(enum_rcrtc_code code, HANDLE context);

/**
 * @brief 通用回调函数定义
 * @param code                          结果码
 * @param context                       用户传入的上下文参数值，用于回调函数
 * @param streams                       用户传入的流句柄
 */
typedef void (*fn_rcrtc_stream_callback)(
    enum_rcrtc_code code,
    HANDLE context,
    HANDLE_STREAM streams[MAX_STREAM_COUNT]);

/**
 * @brief 带json结构结果返回值回调函数原型
 * @param code                          结果码
 * @param json                          json结构
 * @param context                       用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_general_json_callback)(enum_rcrtc_code code,
                                               const char* json,
                                               HANDLE context);

/**
 * @brief 加入房间的回调函数定义
 *
 * @param room_id  房间 id
 * @param code     结果码
 * @param context 用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_join_room_callback)(const char* room_id,
                                            enum_rcrtc_code code,
                                            HANDLE context);

/**
 * @brief 远端用户的流事件回调
 *
 * @param room_id         房间 id
 * @param remote_user_id  远端用户 id
 * @param event           事件类型
 * @param event_param     事件参数
 * @param stream          远端流句柄
 * @param context         用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_remote_stream_callback)(const char* room_id,
                                                const char* remote_user_id,
                                                enum_rcrtc_stream_event event,
                                                void* event_param,
                                                HANDLE_STREAM stream,
                                                HANDLE context);

/**
 * @brief 音视频通道质量
 *
 * @param room_id         房间 id
 * @param local_quality   本地用户音视频质量
 * @param remote_quality  远端用户音视频质量
 * @param remote_count    远端用户个数
 * @param context         用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_user_quality_callback)(
    const char* room_id,
    const rcrtc_quality_t* local_quality,
    const rcrtc_quality_t* remote_quality,
    int32_t remote_count,
    HANDLE context);

/**
 * @brief 音频音量大小
 *
 * @param room_id         房间 id
 * @param remote_vol      远端用户音频质量
 * @param remote_count    远端用户个数
 * @param context         用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_user_audio_energy_callback)(
    const char* room_id,
    const rcrtc_out_vol_t* remote_vol,
    int32_t remote_count,
    HANDLE context);

/**
 * @brief 房间事件回调函数原型
 *
 * @param room_id     房间 id
 * @param user_id     用户 id
 * @param event       事件类型
 * @param event_param 根据事件类型回传的事件参数
 * @param context     用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_room_event_callback)(const char* room_id,
                                             const char* user_id,
                                             enum_rcrtc_room_event event,
                                             void* event_param,
                                             HANDLE context);

/**
 * @brief 视频编码回调函数原型
 *
 * @param user_id     用户 id
 * @param frame       编码视频流二进制数据
 * @param frame_size  视频数据大小
 * @param frame_width 视频分辨率的宽
 * @param frame_height 视频分辨率的高
 * @param timestamp 视频帧的时间戳
 */
typedef void (*fn_rcrtc_encoded_video_frame_callback)(const char* user_id,
                                                      const uint8_t* frame,
                                                      uint32_t frame_size,
                                                      uint32_t frame_width,
                                                      uint32_t frame_height,
                                                      uint32_t timestamp);

/**
 * @brief \ref rcrtc_pcm_speaker_out_register_callback 设置的回调函数类型
 *
 * @param data           pcm 格式音频数据
 * @param size           数据长度
 * @param channels       通道个数
 * @param sample_rate    采样频率
 * @param context        上下文
 */
typedef void (*fn_rcrtc_pcm_speaker_out_data_callback)(const uint8_t* data,
                                                       uint32_t size,
                                                       int32_t channels,
                                                       int32_t sample_rate,
                                                       void* context);

/**
 * @brief 视频数据回调函数原型，数据类型 YUV420：I420
 * 图像内存存处结构如下：
 * yyyyyyyyyyyy....yyyyyyyyyyyy....uuuuuu....vvvvvv...
 * @param  timestamp                    图像时间戳，单位毫秒
 * @param  y                            图像 y 分量
 * @param  u                            图像 u 分量
 * @param  v                            图像 v 分量
 * @param  width                        图像宽度
 * @param  height                       图像高度
 * @param  stride_y                     图像 stride_y 值
 * @param  stride_u                     图像 stride_u 值
 * @param  stride_v                     图像 stride_v 值
 * @param  context                      上下文
 */
typedef void (*fn_rcrtc_video_data_callback)(int64_t timestamp,
                                             const uint8_t* y,
                                             const uint8_t* u,
                                             const uint8_t* v,
                                             int32_t width,
                                             int32_t height,
                                             int32_t stride_y,
                                             int32_t stride_u,
                                             int32_t stride_v,
                                             HANDLE context);

/**
 * @brief 麦克风测试回调函数定义
 * @param value                         当前麦克风音量[0-9]
 * @param context                       用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_mic_test_callback)(int32_t value, HANDLE context);

/**
 * @brief 当前扬声器设备测试回调函数定义
 * @param value                         当前扬声器设备音量[0-9]指针 value
 * @param context                       用户传入的上下文参数值，用于回调函数
 */
typedef void (*fn_rcrtc_spk_test_callback)(int32_t value, HANDLE context);

/**
 * @brief pcm 数据回调
 rcrtc_pcm_register_recording_data_callback 和
 rcrtc_pcm_register_play_data_callback 函数设置的回调函数类型

 * @param[in] data                       音频数据
 * @param[in] size                       音频数据字节长度
 * @param[in] sample_rate                音频数据的采样率
 * @param[in] sample_bits                音频数据采样点数据大小（目前是2字节）
 * @param[in] channels                   音频数据的通道数
 */
typedef void (*rcrtc_pcm_audio_data_cb_func)(uint8_t* data,
                                             uint32_t size,
                                             uint32_t sample_rate,
                                             uint32_t sample_bits,
                                             uint32_t channels);

struct rcrtc_simulation {
  char file_path_[256];
  int32_t channel_;
  int32_t sample_rate_;
};
typedef struct rcrtc_simulation rcrtc_mic_simulation_param;
typedef struct rcrtc_simulation rcrtc_spr_simulation_param;

typedef struct rcrtc_image_cap_simulation_param {
  char file_path_[256];
  int32_t fourcc_;
  int32_t width_;
  int32_t height_;
  enum_rcrtc_video_frame_rate fps_;
} rcrtc_image_cap_simulation_param;

#ifdef __cplusplus
}
#endif

#endif
