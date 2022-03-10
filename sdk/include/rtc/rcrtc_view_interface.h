/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_VIEW_INTERFACE_H
#define RTCLIB_API_RCRTC_VIEW_INTERFACE_H

#include "rcrtc_common.h"
#include "rcrtc_constants.h"

namespace rcrtc {

class RCRTCLIB_API IRCRTCView {
 public:
  //创建渲染配置对象，设置渲染窗口句柄
  static IRCRTCView* create(HANDLE window);

  //销毁渲染配置对象
  static void destroy(IRCRTCView** view);

  virtual ~IRCRTCView() {}

  //设置视频填充方式，默认为 FIT
  virtual void setFitType(RCRTCViewFitType type) = 0;

  //获取视频填充方式
  virtual RCRTCViewFitType getFitType() = 0;

  //设置是否镜像，默认为 false
  virtual void setMirror(bool mirror) = 0;

  //获取是否镜像
  virtual bool getMirror() = 0;

  //获取渲染窗口句柄
  virtual HANDLE getWindowHandle() = 0;
};

}  // namespace rcrtc

#endif
