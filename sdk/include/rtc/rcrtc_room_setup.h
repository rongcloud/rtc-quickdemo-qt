/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_ROOM_SETUP_H
#define RTCLIB_API_RCRTC_ROOM_SETUP_H

#include "rcrtc_common.h"
#include "rcrtc_constants.h"

namespace rcrtc {

class RCRTCAudioSetup;
class RCRTCVideoSetup;

class RCRTCLIB_API RCRTCRoomSetup {
 public:
  static RCRTCRoomSetup* create();
  static bool destroy(RCRTCRoomSetup** setup);

  virtual ~RCRTCRoomSetup();

  // 设置用户角色
  virtual void setRole(RCRTCRole role) = 0;

  // 设置通话类型
  virtual void setMediaType(RCRTCMediaType type) = 0;

  // 设置加入房间类型
  virtual void setJoinType(RCRTCJoinType join_type) = 0;
};
}  // namespace rcrtc

#endif
