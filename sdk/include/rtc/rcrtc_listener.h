/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_LISTENER_H
#define RTCLIB_API_RCRTC_LISTENER_H

#include "rcrtc_common.h"
#include "rcrtc_constants.h"
#include "rcrtc_device.h"

#include <list>
#include <string>

namespace rcrtc {

class RCRTCLIB_API IRCRTCListener {
 public:
  virtual ~IRCRTCListener() {}

  /**
   * 本地用户加入房间回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onRoomJoined(int32_t code, const std::string& errMsg) = 0;

  /**
   * 本地用户离开房间回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onRoomLeft(int32_t code, const std::string& errMsg) = 0;

  /**
   * 引擎内部错误回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onError(int32_t code) = 0;

  /**
   * 本地用户被踢出房间回调
   *
   * @param roomId 房间 id
   * @param errMsg 失败原因
   */
  virtual void onKicked(const std::string& roomId,
                        const std::string& errMsg) = 0;

  /**
   * 远端用户加入房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserJoined(const std::string& userId) = 0;

  /**
   * 远端用户因离线离开房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserOffline(const std::string& userId) = 0;

  /**
   * 远端用户离开房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserLeft(const std::string& userId) = 0;

  /**
   * 远端用户发布资源操作回调
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   */
  virtual void onRemotePublished(const std::string& userId,
                                 RCRTCMediaType type) = 0;

  /**
   * 远端用户取消发布资源操作回调
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   */
  virtual void onRemoteUnpublished(const std::string& userId,
                                   RCRTCMediaType type) = 0;

  /**
   * 远端用户资源状态操作回调
   *
   * @param userId   远端用户UserId
   * @param type     资源类型
   * @param disabled 是否停止相应资源采集
   */
  virtual void onRemoteStateChanged(const std::string& userId,
                                    RCRTCMediaType type,
                                    bool disabled) = 0;

  /**
   * 收到远端用户第一帧数据
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   */
  virtual void onRemoteFirstFrame(const std::string& userId,
                                  RCRTCMediaType type) = 0;

  /**
   * 远端直播合流发布资源操作回调
   *
   * @param type   资源类型
   */
  virtual void onRemoteLiveMixPublished(rcrtc::RCRTCMediaType type) = 0;

  /**
   * 远端直播合流取消发布资源操作回调
   *
   * @param type   资源类型
   */
  virtual void onRemoteLiveMixUnpublished(rcrtc::RCRTCMediaType type) = 0;

  /**
   * 收到直播合流第一帧数据
   *
   * @param type 资源类型
   */
  virtual void onRemoteLiveMixFirstFrame(RCRTCMediaType type) = 0;

  /**
   * 本地用户发布资源回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onPublished(RCRTCMediaType type,
                           int32_t code,
                           const std::string& errMsg) = 0;

  /**
   * 本地用户取消发布资源回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onUnpublished(RCRTCMediaType type,
                             int32_t code,
                             const std::string& errMsg) = 0;

  /**
   * 订阅远端用户发布的资源操作回调
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onSubscribed(const std::string& userId,
                            RCRTCMediaType type,
                            int32_t code,
                            const std::string& errMsg) = 0;

  /**
   * 取消订阅远端用户发布的资源操作回调
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onUnsubscribed(const std::string& userId,
                              RCRTCMediaType type,
                              int32_t code,
                              const std::string& errMsg) = 0;

  /**
   * 订阅合流资源操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixSubscribed(rcrtc::RCRTCMediaType type,
                                   int32_t code,
                                   const std::string& errMsg) = 0;

  /**
   * 取消订阅合流资源操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixUnsubscribed(rcrtc::RCRTCMediaType type,
                                     int32_t code,
                                     const std::string& errMsg) = 0;

  /**
   * 使能摄像头操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onEnableCamera(bool enable,
                              int32_t code,
                              const std::string& errMsg) = 0;

  /**
   * 切换摄像头操作回调
   *
   * @param camera 摄像头信息（函数调用结束，指针即刻销毁）
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg 错误描述
   */
  virtual void onSwitchCamera(const rcrtc::RCRTCCamera* camera,
                              int32_t code,
                              const std::string& errMsg) = 0;

  virtual void onLiveCdnAdded(const std::string& url,
                              int32_t code,
                              const std::string& errMsg) = 0;
  virtual void onLiveCdnRemoved(const std::string& url,
                                int32_t code,
                                const std::string& errMsg) = 0;

  /**
   * 设置合流布局模式操作回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixLayoutModeSet(int32_t code,
                                      const std::string& errMsg) = 0;

  /**
   * 设置合流渲染模式操作回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixRenderModeSet(int32_t code,
                                      const std::string& errMsg) = 0;

  /**
   * 设置合流自定义布局操作回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixCustomLayoutsSet(int32_t code,
                                         const std::string& errMsg) = 0;

  /**
   * 设置合流中参与混音的主播操作回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixCustomAudiosSet(int32_t code,
                                        const std::string& errMsg) = 0;

  /**
   * 设置合流中音频输出码率操作回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixAudioBitrateSet(int32_t code,
                                        const std::string& errMsg) = 0;

  /**
   * 设置合流中视频输出码率操作回调
   *
   * @param tiny 是否是小流
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixVideoBitrateSet(bool tiny,
                                        int32_t code,
                                        const std::string& errMsg) = 0;

  /**
   * 设置合流中视频输出分辨率操作回调
   *
   * @param tiny 是否是小流
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixVideoResolutionSet(bool tiny,
                                           int32_t code,
                                           const std::string& errMsg) = 0;

  /**
   * 设置合流中视频输出帧率操作回调
   *
   * @param tiny 是否是小流
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixVideoFpsSet(bool tiny,
                                    int32_t code,
                                    const std::string& errMsg) = 0;
  /**
   * 设置合流背景颜色操作结果回调
   *
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixBackgroundColorSet(int32_t code,
                                           const std::string& errMsg) = 0;

  virtual void onAudioEffectCreated(int32_t effectId,
                                    int32_t code,
                                    const std::string& errMsg) = 0;

  virtual void onAudioEffectFinished(int32_t effectId) = 0;

  virtual void onAudioMixingStarted() = 0;

  virtual void onAudioMixingPaused() = 0;

  virtual void onAudioMixingStopped() = 0;

  virtual void onAudioMixingFinished() = 0;

  /**
   * @brief 发布自定义流结果通知
   *
   * @param tag  自定义流唯一标志
   * @param type 媒体类型
   * @param code 错误码
   * @param errMsg 错误类型
   *
   * @return void
   */
  virtual void onCustomStreamPublished(const std::string& tag,
                                       rcrtc::RCRTCMediaType type,
                                       int32_t code,
                                       const std::string& errMsg) = 0;
  /**
   * @brief 取消发布自定义流结果通知
   *
   * @param tag    自定义流唯一标志
   * @param type   媒体类型
   * @param code   错误码
   * @param errMsg 错误类型
   *
   * @return void
   */
  virtual void onCustomStreamUnpublished(const std::string& tag,
                                         rcrtc::RCRTCMediaType type,
                                         int32_t code,
                                         const std::string& errMsg) = 0;
  /**
   * @brief 自定义流发布结束通知
   *
   * @param tags   自定义流唯一标志
   * @param type   媒体类型
   *
   * @return void
   */
  virtual void onCustomStreamPublishFinished(const std::string& tag,
                                             rcrtc::RCRTCMediaType type) = 0;
  /**
   * @brief 批量发布自定义流结果通知
   *
   * @param tag 自定义流唯一标志列表
   * @param code 错误码
   * @param errMsg 错误类型
   *
   * @return void
   */
  virtual void onCustomStreamPublished(const std::list<std::string>& tags,
                                       int32_t code,
                                       const std::string& errMsg) = 0;
  /**
   * @brief 批量取消发布自定义流结果通知
   *
   * @param tag    自定义流唯一标志列表
   * @param code   错误码
   * @param errMsg 错误类型
   *
   * @return void
   */
  virtual void onCustomStreamUnpublished(const std::list<std::string>& tags,
                                         int32_t code,
                                         const std::string& errMsg) = 0;
  /**
   * @brief 自定义流发布结束通知
   *
   * @param tags    自定义流唯一标志列表
   *
   * @return void
   */
  virtual void onCustomStreamPublishFinished(
      const std::list<std::string>& tags) = 0;
  /**
   * @brief 远端用户发布自定义流通知
   *
   * @param userId  远端用户id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   *
   * @return void
   */
  virtual void onRemoteCustomStreamPublished(const std::string& userId,
                                             const std::string& tag,
                                             rcrtc::RCRTCMediaType type) = 0;
  /**
   * @brief 远端用户取消发布自定义流通知
   *
   * @param userId  远端用户Id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   *
   * @return void
   */
  virtual void onRemoteCustomStreamUnpublished(const std::string& userId,
                                               const std::string& tag,
                                               rcrtc::RCRTCMediaType type) = 0;
  /**
   * @brief 远端用户取消发布自定义流通知
   *
   * @param userId  远端用户Id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   * @param disabled
   * - true 被禁止发送
   * - false 取消禁止发送
   *
   * @return void
   */
  virtual void onRemoteCustomStreamStateChanged(const std::string& userId,
                                                const std::string& tag,
                                                rcrtc::RCRTCMediaType type,
                                                bool disabled) = 0;
  /**
   * @brief 解码远端自定义视频流第一帧数据通知
   *
   * @param userId  远端用户Id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   *
   * @return void
   */
  virtual void onRemoteCustomStreamFirstFrame(const std::string& userId,
                                              const std::string& tag,
                                              rcrtc::RCRTCMediaType type) = 0;
  /**
   * @brief 订阅指定自定义流结果通知
   *
   * @param userId  远端用户Id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   * @param code    错误码
   * @param errMsg  错误码信息描述
   *
   * @return void
   */
  virtual void onCustomStreamSubscribed(const std::string& userId,
                                        const std::string& tag,
                                        rcrtc::RCRTCMediaType type,
                                        int32_t code,
                                        const std::string& errMsg) = 0;
  /**
   * @brief 取消订阅指定自定义流结果通知
   *
   * @param userId  远端用户Id
   * @param tag     自定义流唯一标志， 全局唯一。
   * @param type    自定义流媒体类型
   * @param code    错误码
   * @param errMsg  错误码信息描述
   *
   * @return void
   */
  virtual void onCustomStreamUnsubscribed(const std::string& userId,
                                          const std::string& tag,
                                          rcrtc::RCRTCMediaType type,
                                          int32_t code,
                                          const std::string& errMsg) = 0;
  /**
   * @brief 批量订阅指定自定义流结果通知
   *
   * @param userId  远端用户Id
   * @param tags    自定义流唯一标志列表。
   * @param code    错误码
   * @param errMsg  错误码信息描述
   *
   * @return void
   */
  virtual void onCustomStreamSubscribed(const std::string& userId,
                                        const std::list<std::string>& tags,
                                        int32_t code,
                                        const std::string& errMsg) = 0;
  /**
   * @brief 批量取消订阅指定自定义流结果通知
   *
   * @param userId  远端用户Id
   * @param tags    自定义流唯一标志列表。
   * @param code    错误码
   * @param errMsg  错误码信息描述
   *
   * @return void
   */
  virtual void onCustomStreamUnsubscribed(const std::string& userId,
                                          const std::list<std::string>& tags,
                                          int32_t code,
                                          const std::string& errMsg) = 0;

  /**
   * 切换角色的回调
   *
   * @param role 当前角色
   * @param code 0: 成功，role 是切换后的角色；非0: 失败，role 保持原来的角色
   * @param errMsg 失败原因
   */
  virtual void onLiveRoleSwitched(rcrtc::RCRTCRole curRole,
                                  int32_t code,
                                  const std::string& errMsg) = 0;

  /**
   * 远端用户切换角色的回调
   *
   * @param roomId 房间 id
   * @param userId 远端用户 id
   * @param role 远端用户当前角色
   */
  virtual void onRemoteLiveRoleSwitched(const std::string& roomId,
                                        const std::string& userId,
                                        rcrtc::RCRTCRole role) = 0;

  /**
   * 获取用户加入的房间信息
   * @param roomInfo 用户加入的房间 id，使用的 设备 id 以及加入时间
   * @param code 0: 成功，；非0: 失败
   */
  virtual void onJoinedRoomGot(const std::list<RCRTCUserJoinedRoom>& roomInfo,
                               int32_t code) = 0;
};

class RCRTCLIB_API IRCRTCMicChangedListener {
 public:
  virtual ~IRCRTCMicChangedListener() {}

  /**
   * @brief 麦克风设备改变
   */
  virtual void onMicrophoneListChanged() = 0;
};

class RCRTCLIB_API IRCRTCSpeakerChangedListener {
 public:
  virtual ~IRCRTCSpeakerChangedListener() {}

  /**
   * @brief 扬声器设备改变
   */
  virtual void onSpeakerListChanged() = 0;
};

class RCRTCLIB_API IRCRTCCameraChangedListener {
 public:
  virtual ~IRCRTCCameraChangedListener() {}
  /**
   * @brief 摄像头设备改变
   */
  virtual void onCameraListChanged() = 0;
};

class RCRTCLIB_API IRCRTCStatsListener {
 public:
  virtual ~IRCRTCStatsListener() {}
  virtual void onNetworkStats(RCRTCNetworkStats& stats) = 0;
  virtual void onLocalAudioStats(RCRTCAudioStats stats) = 0;
  virtual void onLocalVideoStats(RCRTCVideoStats stats) = 0;
  virtual void onRemoteAudioStats(const std::string& userId,
                                  RCRTCAudioStats stats) = 0;
  virtual void onRemoteVideoStats(const std::string& userId,
                                  RCRTCVideoStats stats) = 0;
  virtual void onLiveMixAudioStats(RCRTCAudioStats stats) = 0;
  virtual void onLiveMixVideoStats(RCRTCVideoStats stats) = 0;
  virtual void onLocalCustomAudioStats(const std::string& tag,
                                       RCRTCAudioStats stats) = 0;
  virtual void onLocalCustomVideoStats(const std::string& tag,
                                       RCRTCVideoStats stats) = 0;
  virtual void onRemoteCustomAudioStats(const std::string& userId,
                                        const std::string& tag,
                                        RCRTCAudioStats stats) = 0;
  virtual void onRemoteCustomVideoStats(const std::string& userId,
                                        const std::string& tag,
                                        RCRTCVideoStats stats) = 0;
};

class RCRTCLIB_API RCRTCWritableAudioFrameListener {
 public:
  virtual ~RCRTCWritableAudioFrameListener() {}

  virtual void onAudioFrame(RCRTCAudioFrame* frame) = 0;
};

class RCRTCLIB_API RCRTCReadableAudioFrameListener {
 public:
  virtual ~RCRTCReadableAudioFrameListener() {}

  virtual void onAudioFrame(RCRTCAudioFrame* frame) = 0;
};

class RCRTCLIB_API RCRTCWritableVideoFrameListener {
 public:
  virtual ~RCRTCWritableVideoFrameListener() {}

  virtual void onVideoFrame(RCRTCVideoFrame* frame) = 0;
};

class RCRTCLIB_API RCRTCReadableVideoFrameListener {
 public:
  virtual ~RCRTCReadableVideoFrameListener() {}

  virtual void onVideoFrame(RCRTCVideoFrame* frame) = 0;
};
}  // namespace rcrtc
#endif
