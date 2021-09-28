/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_EXTENSION_LIBC_VIDEO_CODEC_EXTERN_H_
#define RCRTCLIB_EXTENSION_LIBC_VIDEO_CODEC_EXTERN_H_

/*
 * @notice: just for server api. public for server side.
 */

#include <libc_rtc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum enum_rcrtc_video_codec_error {
  RCRTC_VIDEO_CODEC_OK_REQUEST_KEYFRAME = 4,
  RCRTC_VIDEO_CODEC_NO_OUTPUT = 1,
  RCRTC_VIDEO_CODEC_OK = 0,
  RCRTC_VIDEO_CODEC_ERROR = -1,
  RCRTC_VIDEO_CODEC_MEMORY_ERROR = -3,
  RCRTC_VIDEO_CODEC_PARAMETER_ERROR = -4,
  RCRTC_VIDEO_CODEC_UNINITIALIZED_ERROR = -7,
  RCRTC_VIDEO_CODEC_FALLBACK_SOFTWARE_ERROR = -13,
  RCRTC_VIDEO_CODEC_TARGET_BITRATE_OVERSHOOT_ERROR = -14,
  RCRTC_VIDEO_CODEC_SIMULCAST_PARAMETER_UNSUPPORTED = -15,
} enum_rcrtc_video_codec_error;

typedef enum enum_rcrtc_video_codec_type {
  RCRTC_VIDEO_CODEC_TYPE_GENERIC = 0,
  RCRTC_VIDEO_CODEC_TYPE_VP8,
  RCRTC_VIDEO_CODEC_TYPE_VP9,
  RCRTC_VIDEO_CODEC_TYPE_H264,
  RCRTC_VIDEO_CODEC_TYPE_MULTIPLEX,
} enum_rcrtc_video_codec_type;

typedef enum enum_rcrtc_h264_profile {
  RCRTC_H264_PROFILE_CONSTRAINED_BASELINE,
  RCRTC_H264_PROFILE_BASELINE,
  RCRTC_H264_PROFILE_MAIN,
  RCRTC_H264_PROFILE_CONSTRAINED_HIGH,
  RCRTC_H264_PROFILE_HIGH,
} enum_rcrtc_h264_profile;

typedef enum enum_rcrtc_video_codec_mode {
  RCRTC_VIDEO_CODEC_MODE_REALTIME_VIDEO,
  RCRTC_VIDEO_CODEC_MODE_SCREEN_SHARING,
} enum_rcrtc_video_codec_mode;

typedef struct rcrtc_video_codec_t {
  enum_rcrtc_video_codec_type codec_type;
  unsigned char payload_type;
  uint16_t width;
  uint16_t height;

  uint32_t start_bitrate;  // kilobits/sec.
  uint32_t max_bitrate;    // kilobits/sec.
  uint32_t min_bitrate;    // kilobits/sec.

  uint32_t max_frame_rate;
  enum_rcrtc_video_codec_mode mode;
} rcrtc_video_codec_t;

typedef enum enum_rcrtc_frame_type {
  RCRTC_FRAME_TYPE_EMPTY_FRAME = 0,
  RCRTC_FRAME_TYPE_VIDEO_FRAME_KEY = 3,
  RCRTC_FRAME_TYPE_VIDEO_FRAME_DELTA = 4,
} enum_rcrtc_frame_type;

typedef struct rcrtc_video_sdp_format_t {
  char name[256];
} rcrtc_video_sdp_format_t;

typedef struct rcrtc_frame_buffer_t {
  const uint8_t* Y_;
  int32_t Y_Stride_;
  const uint8_t* U_;
  int32_t U_Stride_;
  const uint8_t* V_;
  int32_t V_Stride_;
  int32_t width_;
  int32_t height_;
} rcrtc_frame_buffer_t;

typedef struct rcrtc_video_frame_t {
  struct rcrtc_frame_buffer_t frame_buffer_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
  int64_t timestamp_us_;
} rcrtc_video_frame_t;

typedef struct rcrtc_encoded_buffer_t {
  uint8_t* data_;
  uint32_t length_;
} rcrtc_encoded_buffer_t;

typedef struct rcrtc_encoded_frame_t {
  struct rcrtc_encoded_buffer_t buffer_;
  enum_rcrtc_frame_type frame_type_;
  uint32_t width_;
  uint32_t height_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
  int64_t timestamp_us_;
} rcrtc_encoded_frame_t;

typedef int32_t (*fn_rcrtc_encode_init)(
    HANDLE handle_extern_encoder,
    const rcrtc_video_codec_t* codec_settings,
    int32_t number_of_cores,
    size_t max_payload_size);

typedef int32_t (*fn_rcrtc_encode_release)(HANDLE handle_extern_encoder);

typedef void (*fn_rcrtc_encode_dispose)(HANDLE handle_extern_encoder);

typedef int32_t (*fn_rcrtc_encode_encode)(HANDLE handle_extern_encoder,
                                          const rcrtc_video_frame_t* frame,
                                          const bool request_key_frame,
                                          HANDLE context);

typedef int32_t (*fn_rcrtc_encode_set_rate)(HANDLE handle_extern_encoder,
                                            uint32_t bitrate,
                                            uint32_t framerate);

typedef struct rcrtc_video_encoder_adapt_t {
  fn_rcrtc_encode_init init;
  fn_rcrtc_encode_release release;
  fn_rcrtc_encode_dispose dispose;
  fn_rcrtc_encode_encode encode;
  fn_rcrtc_encode_set_rate set_rate;
  void* extra_context;
} rcrtc_video_encoder_adapt_t;

typedef int32_t (*fn_rcrtc_encode_supported_format)(
    rcrtc_video_sdp_format_t* formats,
    int32_t count);

typedef int32_t (*fn_rcrtc_encode_create)(rcrtc_video_sdp_format_t format,
                                          HANDLE* handle_extern_encoder,
                                          rcrtc_video_encoder_adapt_t* adapt);

typedef struct rcrtc_video_encoder_adapt_factory_t {
  /*
   * 工厂支持的编码器类型查询函数, 目前只支持 h264 I P 帧编码方式
   */
  fn_rcrtc_encode_supported_format supported_format;
  /*
   * 创建指定编码器对象，目前只支持 h264 I P 帧编码方式
   */
  fn_rcrtc_encode_create create_encoder;
} rcrtc_video_encoder_adapt_factory_t;

/**
 * @brief 设定外部视频编码库工厂, 只支持 h264 编码 I P 帧编码方式
 * @param handle                       引擎句柄
 * @param encoder_factory              编码器工厂函数集合
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_codec_extern_set_encoder_factory(
    HANDLE_RTC_ENGINE handle,
    rcrtc_video_encoder_adapt_factory_t* encoder_factory);

/**
 * @brief 设定外部视频编码库工厂, 只支持 h264 编码 I P 帧编码方式
 * @param handle                       外部编码器句柄
 * @param frame                       编码数据编码数据结构指针
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_encode_deliver_encoded_frame(
    HANDLE handle,
    const rcrtc_encoded_frame_t* frame);

///////////////////////////////////////////////////////////////////////////////
//视频解码相关
///////////////////////////////////////////////////////////////////////////////
typedef struct rcrtc_encodec_image_t {
  rcrtc_encoded_buffer_t buffer_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
} rcrtc_encodec_image_t;

typedef int32_t (*fn_rcrtc_decode_init)(
    HANDLE handle_extern_decoder,
    const rcrtc_video_codec_t* codec_settings,
    int32_t number_of_cores);

typedef int32_t (*fn_rcrtc_decode_decode)(
    HANDLE handle_extern_decoder,
    const rcrtc_encodec_image_t* input_image,
    bool missing_frames,
    int64_t render_time_ms,
    HANDLE decoded_handle);

typedef int32_t (*fn_rcrtc_decode_release)(HANDLE handle_extern_decoder);

typedef int32_t (*fn_rcrtc_decode_prefers_late_decoding)(
    HANDLE handle_extern_decoder);

typedef const char* (*fn_rcrtc_decode_implementation_name)(
    HANDLE handle_extern_decoder);

typedef struct rcrtc_video_decoder_adapt_t {
  fn_rcrtc_decode_init init;
  fn_rcrtc_decode_decode decode;
  fn_rcrtc_decode_release release;
  fn_rcrtc_encode_dispose dispose;
  fn_rcrtc_decode_prefers_late_decoding prefers_late_decoding;
  fn_rcrtc_decode_implementation_name implementation_name;
} rcrtc_video_decoder_adapt_t;

typedef int32_t (*fn_rcrtc_decode_supported_format)(
    rcrtc_video_sdp_format_t* formats,
    int32_t count);

typedef int32_t (*fn_rcrtc_decoder_create)(rcrtc_video_sdp_format_t format,
                                           HANDLE* handle_extern_decoder,
                                           rcrtc_video_decoder_adapt_t* adapt);
/*
 * 视频解码器工厂函数指针集合.
 */
typedef struct rcrtc_video_decoder_adapt_factory {
  /*
   * 工厂支持的解码器类型查询函数, 目前只支持 h264
   */
  fn_rcrtc_decode_supported_format supported_format;
  /*
   * 创建指定解码器对象，目前只支持H264
   */
  fn_rcrtc_decoder_create create_decoder;
} rcrtc_video_decoder_adapt_factory_t;

/**
 * @brief 设定外部视频解码库工厂, 只支持 h264 编码
 * @param handle                        引擎句柄
 * @param decoder_factory               解码器工厂函数集合
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_codec_extern_set_decoder_factory(
    HANDLE_RTC_ENGINE handle,
    rcrtc_video_decoder_adapt_factory_t* decoder_factory);

/**
 * @brief 设定外部视频解码库工厂, 只支持 h264 解码
 * @param handle                              外部解码器句柄
 * @param video_frame                   解码后的图像数据结构
 * @return
 * - 0：成功
 * - -1：失败
 */
RCRTCLIB_API
int32_t rcrtc_video_decode_deliver_image_frame(
    HANDLE handle,
    const rcrtc_video_frame_t* video_frame);

#ifdef __cplusplus
}
#endif

#endif
