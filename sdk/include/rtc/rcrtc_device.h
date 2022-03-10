/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_DEVICE_H
#define RTCLIB_API_RCRTC_DEVICE_H

#include "rcrtc_common.h"

#include <string>
#if defined(WIN32)
#include <windows.h>
#endif
namespace rcrtc {

#if defined(WIN32)
typedef HWND DesktopSourceId;
#else
typedef void* DesktopSourceId;
#endif

class RCRTCLIB_API RCRTCDevice {
 public:
  explicit RCRTCDevice(std::string name, std::string id, int32_t index);
  RCRTCDevice() = delete;

  virtual ~RCRTCDevice();

  void setName(const std::string& name);

  const char* getCStringName() const;

  void setIndex(int32_t index);

  int32_t getIndex() const;

  void setId(const std::string& id);

  const char* getId() const;

 private:
  std::string name_;
  std::string id_;
  int32_t index_;
};

class RCRTCLIB_API RCRTCSpeaker : public RCRTCDevice {
 public:
  RCRTCSpeaker() = delete;
  explicit RCRTCSpeaker(std::string name, std::string id, int32_t index);

  ~RCRTCSpeaker() override;
};

class RCRTCLIB_API RCRTCMicrophone : public RCRTCDevice {
 public:
  RCRTCMicrophone() = delete;
  explicit RCRTCMicrophone(std::string name, std::string id, int32_t index);

  ~RCRTCMicrophone() override;
};

class RCRTCLIB_API RCRTCCamera : public RCRTCDevice {
 public:
  RCRTCCamera() = delete;
  explicit RCRTCCamera(std::string name, std::string id, int32_t index);

  ~RCRTCCamera() override;
};

class RCRTCLIB_API RCRTCDesktopSource : public RCRTCDevice {
 public:
  RCRTCDesktopSource() = delete;
  explicit RCRTCDesktopSource(std::string name,
                              std::string id,
                              int32_t index,
                              DesktopSourceId source_id);

  ~RCRTCDesktopSource() override;
  DesktopSourceId GetSourceId();

 private:
  DesktopSourceId source_id_;
};

}  // namespace rcrtc

#endif
