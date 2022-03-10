/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_CONFIG_H
#define RTCLIB_API_RCRTC_CONFIG_H

#include "rcrtc_common.h"
#include "rcrtc_constants.h"

namespace rcrtc {

class RCRTCLIB_API RCRTCAudioConfig {
 public:
  // 创建音频配置对象指针
  static RCRTCAudioConfig* create();

  // 销毁音频配置对象指针
  static bool destroy(RCRTCAudioConfig** config);

  virtual ~RCRTCAudioConfig();

  // 设置音频质量
  virtual void SetAudioQuality(RCRTCAudioQuality quality) = 0;

  // 获取音频质量
  virtual RCRTCAudioQuality GetAudioQuality() = 0;

  // 设置音频场景
  virtual void SetAudioScenario(RCRTCAudioScenario scenario) = 0;

  // 获取音频场景
  virtual RCRTCAudioScenario GetAudioScenario() = 0;
};

class RCRTCLIB_API RCRTCVideoConfig {
 public:
  // 创建视频配置对象指针
  static RCRTCVideoConfig* create();

  // 销毁视频配置对象指针
  static bool destroy(RCRTCVideoConfig** config);

  virtual ~RCRTCVideoConfig();

  // 获取最小码率
  virtual int32_t getMinBitrate() const = 0;

  // 设置最小码率
  virtual void setMinBitrate(int32_t minBitrate) = 0;

  // 获取最大码率
  virtual int32_t getMaxBitrate() const = 0;

  // 设置最大码率
  virtual void setMaxBitrate(int32_t maxBitrate) = 0;

  // 获取帧率
  virtual RCRTCVideoFps getFps() const = 0;

  // 设置帧率
  virtual void setFps(RCRTCVideoFps fps) = 0;

  // 获取分辨率
  virtual RCRTCVideoResolution getResolution() const = 0;

  // 设置分辨率
  virtual void setResolution(RCRTCVideoResolution resolution) = 0;

  // 当前画面是否镜像
  virtual bool isMirror() const = 0;

  // 设置当前画面镜像效果
  virtual void setMirror(bool mirror) = 0;

  // 根据设置的分辨率与帧率获取合适的码率范围
  virtual bool getMaxAndMinBitrate(int32_t* max_bitrate_kbps,
                                   int32_t* min_bitrate_kbps) = 0;
};

}  // namespace rcrtc
#endif
