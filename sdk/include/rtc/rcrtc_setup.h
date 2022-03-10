/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_SETUP_H
#define RTCLIB_API_RCRTC_SETUP_H

#include "rcrtc_common.h"
#include "rcrtc_constants.h"

#include <memory>
#include <string>

namespace rcrtc {

class RCRTCAudioSetup;
class RCRTCVideoSetup;
class RCRTCLogSetup;

class RCRTCLIB_API RCRTCEngineSetup {
 public:
  virtual ~RCRTCEngineSetup();
  static RCRTCEngineSetup* create();
  static bool destroy(RCRTCEngineSetup** setup);

  //音频配置参数，暂不支持，sdk 使用默认配置
  virtual RCRTCAudioSetup* CreateAudioSetup() = 0;

  //视频配置参数，如果不设置，则使用 sdk 默认配置
  virtual RCRTCVideoSetup* CreateVideoSetup() = 0;

  //日志配置参数，如果不设置，则使用 sdk 默认配置
  virtual RCRTCLogSetup* CreateLogSetup() = 0;

  //设置媒体服务器的 url，如果不设置，则使用通过导航获取的 url
  virtual void setMediaUrl(const std::string& mediaUrl) = 0;

  //设置断网后是否自动重连（超过 1 分钟不再重连），默认为 false
  virtual void setReconnectable(bool reconnectable) = 0;

  //设置状态上报间隔，默认为 2 秒
  virtual void setStatusReportInterval(int32_t statusReportInterval) = 0;

  //设置是否使用 SRTP，默认为 false
  virtual void setEnableSRTP(bool enableSRTP) = 0;
};

//该接口暂不支持
class RCRTCLIB_API RCRTCAudioSetup {
 public:
  virtual ~RCRTCAudioSetup() {}
  virtual void setAudioCodecType(RCRTCAudioCodecType type) = 0;
  virtual void setAudioSource(int32_t audioSource) = 0;
  virtual void setAudioSampleRate(int32_t audioSampleRate) = 0;
  virtual void setEnableMicrophone(bool enableMicrophone) = 0;
  virtual void setEnableStereo(bool enableStereo) = 0;
};

//该接口只支持设置发布视频流时，是否发布小流
class RCRTCLIB_API RCRTCVideoSetup {
 public:
  virtual ~RCRTCVideoSetup() {}
  virtual void setEnableHardwareDecoder(bool enable) = 0;
  virtual void setEnableHardwareEncoder(bool enable) = 0;
  virtual void setEnableHardwareEncoderHighProfile(bool enable) = 0;
  virtual void setHardwareEncoderFrameRate(int32_t frameRate) = 0;
  virtual void setEnableEncoderTexture(bool enable) = 0;
  
  // 是否发布小流
  virtual void setEnableTinyStream(bool enable) = 0;
};

class RCRTCLIB_API RCRTCLogSetup {
 public:
  virtual ~RCRTCLogSetup() {}
  //日志目录（必须真实存在），如果不设置，则不会生成日志文件
  virtual void setLogFolder(const std::string& folder) = 0;

  //是否使能自动删除日志文件，默认为 false
  virtual void setEnableAutoDeletedFile(bool enable) = 0;

  //是否使能自动检查日志文件大小，默认为 false
  virtual void setEnableAutoCheckSize(bool enable) = 0;

  //日志保留的时间（单位 天），默认为 7
  virtual void setLogRetentionPeriod(uint64_t period) = 0;

  //日志文件大小的限制（单位 MB），默认为 2 G
  virtual void setLogSizeLimit(uint64_t limit) = 0;

  //日志级别，默认为 1
  virtual void setLogLevel(uint64_t level) = 0;
};
}  // namespace rcrtc

#endif