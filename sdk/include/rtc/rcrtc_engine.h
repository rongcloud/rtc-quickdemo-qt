/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_ENGINE_H
#define RTCLIB_API_RCRTC_ENGINE_H

#include "rcrtc_common.h"
#include "rcrtc_config.h"
#include "rcrtc_constants.h"
#include "rcrtc_listener.h"
#include "rcrtc_room_setup.h"
#include "rcrtc_setup.h"
#include "rcrtc_view_interface.h"

#include "rcim_client.h"

#include <list>
#include <string>

#define MAX_DEVICE_NUMBERS 5

namespace rcrtc {

class RCRTCCamera;
class RCRTCMicrophone;
class RCRTCSpeaker;

class RCRTCLIB_API RCRTCEngine {
 public:
  static RCRTCEngine* create(HANDLE_IM_ENGINE imEngine,
                             RCRTCEngineSetup* setup);

  static RCRTCEngine* create(HANDLE_IM_ENGINE imEngine);

  virtual ~RCRTCEngine() {}

  /**
   * 引擎异步回调通知
   *
   * @param listener 设置的回调监听接口
   */
  virtual void setListener(IRCRTCListener* listener) = 0;

  /**
   * 引擎状态异步回调通知
   * @param listener
   */
  virtual void setStatsListener(IRCRTCStatsListener* listener) = 0;

  /**
   * 销毁引擎
   */
  virtual void destroy() = 0;

  /**
   * 加入房间
   *
   * @param roomId 房间 id
   * @return 0: 成功, 非0: 失败
   */

  virtual int32_t joinRoom(const std::string& roomId) = 0;

  /**
   * 加入房间
   *
   * @param roomId 房间 id
   * @param setup 房间配置信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t joinRoom(const std::string& roomId,
                           RCRTCRoomSetup* setup) = 0;

  /**
   * 离开房间
   *
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t leaveRoom() = 0;

  /**
   * 加入房间后, 发布本地资源
   *
   * @param type 资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t publish(RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 取消发布已经发布的本地资源
   *
   * @param type 资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t unpublish(RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 订阅远端用户发布的资源
   *
   * @param userIds 远端用户 UserId 列表
   * @param type    资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t subscribe(const std::list<std::string>& userIds,
                            RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 订阅远端用户发布的资源,
   *
   * @param userIds 远端用户 UserId 列表
   * @param type    资源类型
   * @param tiny    视频小流, true:订阅视频小流 false:订阅视频大流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t subscribe(const std::list<std::string>& userIds,
                            RCRTCMediaType type,
                            bool tiny) = 0;

  /**
   * 加入房间后, 订阅远端用户发布的资源
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t subscribe(const std::string& userId, RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 订阅远端用户发布的资源
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   * @param tiny   视频小流, true:订阅视频小流 false:订阅视频大流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t subscribe(const std::string& userId,
                            RCRTCMediaType type,
                            bool tiny) = 0;

  /**
   * 加入房间后, 取消订阅远端用户发布的资源
   *
   * @param userIds 远端用户 UserId 列表
   * @param type    资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t unsubscribe(const std::list<std::string>& userIds,
                              RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 取消订阅远端用户发布的资源
   *
   * @param userIds 远端用户 UserId 列表
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t unsubscribe(const std::list<RCRTCSubscribeInfo>& userIds) = 0;

  /**
   * 加入房间后, 取消订阅远端用户发布的资源
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t unsubscribe(const std::string& userId,
                              RCRTCMediaType type) = 0;

  /**
   * 加入房间后, 订阅发布的混合资源
   *
   * @param type   资源类型
   * @param tiny   视频小流, true:订阅视频小流 false:订阅视频大流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t subscribeLiveMix(RCRTCMediaType type, bool tiny = false) = 0;

  /**
   * 加入房间后, 取消订阅发布的混合资源
   *
   * @param type    资源类型
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t unsubscribeLiveMix(RCRTCMediaType type) = 0;

  /**
   * 音频参数配置
   *
   * @param config 音频配置信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setAudioConfig(RCRTCAudioConfig* config) = 0;

  /**
   * 视频参数配置
   *
   * @param config 视频配置信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setVideoConfig(RCRTCVideoConfig* config) = 0;

  /**
   * 视频小流参数配置
   *
   * @param config 视频配置信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setTinyVideoConfig(RCRTCVideoConfig* config) = 0;

  /**
   * 获取摄像头设备列表
   *
   * @return
   */
  virtual int32_t getCameraList(std::list<RCRTCCamera*>& list) = 0;

  /**
   * 获取麦克风设备列表
   */
  virtual int32_t getMicrophoneList(std::list<RCRTCMicrophone*>& list) = 0;

  /**
   * 设置麦克风设备列表改变监听
   *
   * @param listener 设置的回调监听接口
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setMicrophoneChangedListener(
      IRCRTCMicChangedListener* listener) = 0;

  /**
   * 开启指定麦克风设备
   * @param microphone  麦克风设备详细信息
   * @param asDefault   是否设置为默认音频流采集设备
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t enableMicrophone(RCRTCMicrophone* microphone,
                                   bool asDefault = true) = 0;

  /**
   * 关闭指定麦克风设备
   * @param microphone  麦克风设备详细信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t disableMicrophone(RCRTCMicrophone* microphone) = 0;

  /**
   * 打开/关闭声音设备
   *
   * @param enable true 打开, false 关闭
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t enableAudio(bool enable) = 0;

  /**
   * 调整麦克风的音量
   *
   * @param volume 0 ~ 100, 默认值: 100
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t adjustLocalVolume(uint32_t volume) = 0;

  /**
   * 调整扬声器的音量
   *
   * @param volume 0 ~ 100, 默认值: 100
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t adjustRemoteVolume(uint32_t volume) = 0;

  /**
   * 获取扬声器设备列表
   *
   */
  virtual int32_t getSpeakerList(std::list<RCRTCSpeaker*>& list) = 0;

  /**
   * 设置扬声器设备列表改变监听
   *
   * @param listener 设置的回调监听接口
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setSpeakerListChangedListener(
      IRCRTCSpeakerChangedListener* listener) = 0;

  /**
   * 开启指定扬声器设备
   * @param speaker  扬声器设备详细信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t enableSpeaker(RCRTCSpeaker* speaker) = 0;

  /**
   * 关闭指定扬声器设备
   * @param speaker  扬声器设备详细信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t disableSpeaker(RCRTCSpeaker* speaker) = 0;

  /**
   * 设置摄像头设备列表改变监听
   *
   * @param listener 设置的回调监听接口
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setCameraListChangedListener(
      IRCRTCCameraChangedListener* listener) = 0;

  /**
   * 开启指定摄像头设备
   * @param camera  摄像头设备详细信息
   * @param asDefault   是否设置为默认视频流采集设备
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t enableCamera(RCRTCCamera* camera, bool asDefault = true) = 0;

  /**
   * 关闭指定摄像头设备
   * @param speaker  摄像头设备详细信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t disableCamera(RCRTCCamera* camera) = 0;

  /**
   * 切换摄像头
   *
   * @param camera 摄像头信息
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t switchToCamera(RCRTCCamera* camera) = 0;

  /**
   * 获取当前使用摄像头位置
   *
   * @return 摄像头信息
   */
  virtual int32_t whichCamera(RCRTCCamera** camera) = 0;

  /**
   * 设置本地视频 view
   *
   * @param view  本地视频窗口
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLocalView(IRCRTCView* view) = 0;

  /**
   * 移除本地视频 view
   *
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t removeLocalView() = 0;

  /**
   * 设置远端视频 view
   *
   * @param userId 远端用户的 userId
   * @param view   RRCRTCView 对象
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setRemoteView(const std::string& userId,
                                IRCRTCView* view) = 0;

  /**
   * 移除远端视频 view
   *
   * @param userId 远端用户的 userId
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t removeRemoteView(const std::string& userId) = 0;

  /**
   * 设置合流视频 view
   *
   * @param view   RRCRTCView 对象
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixView(IRCRTCView* view) = 0;

  /**
   * 移除合流视频 view
   *
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t removeLiveMixView() = 0;
  /**
   * 停止本地数据发送
   *
   * @param type 资源类型
   * @param mute true: 不发送数据 false: 发送数据
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t muteLocalStream(RCRTCMediaType type, bool mute) = 0;

  /**
   * 停止远端数据渲染
   *
   * @param userId 远端用户的 userId
   * @param type   资源类型
   * @param mute   true: 不渲染 false: 渲染
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t muteRemoteStream(const std::string& userId,
                                   RCRTCMediaType type,
                                   bool mute) = 0;

  /**
   * 获取房间会话Id
   *
   * @return session id
   */
  virtual const char* getSessionId() = 0;

  /**
   * 利用文件创建自定义音视频流
   *
   * @param path 文件的绝对路径（带有文件后缀名）
   * @param tag   自定义流的唯一标志
   * @param type   创建自定义流的音视频类型
   * @param replace  在音频类型时，是否替换默认发送的音频数据
   * @param playback 在音频类型时， 是否回放音频数据
   * @return
   */
  virtual int32_t createCustomStreamFromFile(const std::string& path,
                                             const std::string& tag,
                                             RCRTCMediaType type,
                                             bool replace,
                                             bool playback) = 0;

  /**
   * 利用视频文件创建自定义视频
   *
   * @param path     文件的绝对路径（带有文件后缀名）
   * @param tag      自定义流的唯一标志
   * @param format   yuv 数据存储格式，目前仅支持 YUV420P
   * @return         0: 成功, 非0: 失败
   * @remark:        目前仅支持未经编码的 yuv 数据文件
   *    
   */
  virtual int32_t createCustomVideoFromFile(
      const std::string& path,
      const std::string& tag,
      int32_t width,
      int32_t height,
      RCRTCVideoFps fps,
      RCRTCVideoFormat format = RCRTCVideoFormat::YUV420P) = 0;
  /**
   * @brief 创建一个指定摄像头的共享视频流，指定采集的摄像头信息。
   * (摄像头信息由 getCameraList 获取）
   *
   * @param camera 摄像头信息
   * @param tag 要创建的流的唯一标志，全局唯一。
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   */
  virtual int32_t createCustomStreamFromVideoDevice(RCRTCCamera* camera,
                                                    const std::string& tag) = 0;
  /**
   * 利用麦克风创建自定义音视频流
   *
   * @param microphone 麦克风信息
   * @param tag   自定义流的唯一标志
   * @param replace  在音频类型时，是否替换默认发送的音频数据
   * @param playback 在音频类型时， 是否回放音频数据
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t createCustomStreamFromAudioDevice(RCRTCMicrophone* microphone,
                                                    const std::string& tag,
                                                    bool replace,
                                                    bool playback) = 0;
  /**
   * @brief 获取当前的显示器列表
   *
   * @param list 存储显示器列表的 RCRTCDesktopSource list
   * @return
   * - 成功返回：0
   * - 失败返回：非0值，详见错误码
   * @remark:
   * 返回的显示器信息指针的生命周期由底层SDK维护，每次调用该接口，原有的指针将失效，不可再次使用；
   *          调用该接口前需要创建并初始化引擎信息。
   */
  virtual int32_t getMonitorList(std::list<RCRTCDesktopSource*>& list) = 0;

  /**
   * @brief 创建一个屏幕的共享视频流，指定采集的显示器信息
   * (显示器信息由 getMonitorList 获取）
   *
   * @param source 显示器信息
   * @param tag    要创建的流的唯一标志，全局唯一。
   * @param share_audio   是否共享电脑音频，默认不共享。
   * @param list   共享时需要过滤的应用窗口，nullptr 时不过滤任何窗口。
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   */
  virtual int32_t createCustomStreamByMonitor(
      RCRTCDesktopSource* source,
      const std::string& tag,
      bool share_audio = false,
      std::list<RCRTCDesktopSource*>* list = nullptr) = 0;

  /**
   * @brief 获取当前的窗口列表
   *
   * @param list 存储窗口列表的指针数组
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   * @remark:
   * 返回的窗口指针的生命周期由底层SDK维护，每次调用该接口，原有的指针将失效，不可再次使用；
   *          调用该接口前需要创建并初始化引擎信息。
   */
  virtual int32_t getCaptureWindowList(
      std::list<RCRTCDesktopSource*>& list) = 0;

  /**
   * @brief 创建一个应用窗口的共享视频流，指定采集的应用窗口信息
   * (应用窗口信息由 getCaptureWindowList 获取）
   *
   * @param source 应用窗口信息
   * @param tag 要创建的流的唯一标志，全局唯一。
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   */
  virtual int32_t createCustomStreamByWindow(RCRTCDesktopSource* source,
                                             const std::string& tag) = 0;

  /**
   * @brief 创建一个屏幕指定区域的共享视频流，指定采集的屏幕的区域。
   *
   * @param rect_x 屏幕采集区域矩形左上角横轴坐标
   * @param rect_y 屏幕采集区域矩形左上角纵轴坐标
   * @param rect_w 屏幕采集区域矩形宽度，宽度必须大于0
   * @param rect_h 屏幕采集区域矩形高度，高度必须大于0
   * @param tag 要创建的流的唯一标志，全局唯一。
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   */
  virtual int32_t createCustomStreamByMonitorRect(int32_t rect_x,
                                                  int32_t rect_y,
                                                  int32_t rect_w,
                                                  int32_t rect_h,
                                                  const std::string& tag) = 0;

  /**
   * @brief 销毁指定的自定义流
   *
   * @param tags 自定义流的唯一标志列表
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   */
  virtual int32_t destroyCustomStream(const std::list<std::string>& tags) = 0;

  /**
   * @brief 配置自自定义视频流码率、分辨率、是否镜像等参数
   *
   * @param tag 自定义流的唯一标志
   * @param config 视频配置
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已存在的自定义流进行配置；
   */
  virtual int32_t setCustomStreamVideoConfig(const std::string& tag,
                                             RCRTCVideoConfig* config) = 0;

  /**
   * @brief 自定义音频流的情景模式、质量进行配置
   *
   * @param tag 自定义流的唯一标志
   * @param config 音频配置
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已存在的自定义流进行配置；
   */
  virtual int32_t setCustomStreamAudioConfig(const std::string& tag,
                                             RCRTCAudioConfig* config) = 0;
  /**
   * @brief 取消本地自定义流的数据发送。
   *
   * @param tag 自定义流的唯一标志
   * @param type 自定义流的媒体类型（仅支持 rcrtc::RCRTCMediaType::AUDIO 或
   * rcrtc::RCRTCMediaType::VIDEO ）
   * @param mute
   * - true  禁止发送数据
   * - false 允许发送数据
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已发布的自定义流设置；
   */
  virtual int32_t muteLocalCustomStream(const std::string& tag,
                                        RCRTCMediaType type,
                                        bool mute) = 0;

  /**
   * @brief 设置自定义视频流设置渲染窗体。
   *
   * @param tag 自定义流的唯一标志
   * @param view 渲染窗体
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已存在的自定义流进行配置；
   */
  virtual int32_t setLocalCustomStreamView(const std::string& tag,
                                           IRCRTCView* view) = 0;

  /**
   * @brief 取消绑定自定义视频流渲染窗体。
   *
   * @param tag 自定义流的唯一标志
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已存在的自定义流进行配置；
   */
  virtual int32_t removeLocalCustomStreamView(const std::string& tag) = 0;

  /**
   * @brief 发布指定自定义流
   *
   * @param tag 自定义流的唯一标志
   * @param type 自定义流的媒体类型
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 自定义流的 tag 和媒体类型 type 必须匹配，当二者不匹配时会导致
   *          自定义流发布失败。
   */
  virtual int32_t publishCustomStream(const std::string& tag,
                                      RCRTCMediaType type) = 0;

  /**
   * @brief 取消发布指定自定义流
   *
   * @param tag 自定义流的唯一标志
   * @param type 自定义流的媒体类型
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 自定义流的 tag 和媒体类型 type 必须匹配，当二者不匹配时会导致
   *          自定义流取消发布失败。
   */
  virtual int32_t unpublishCustomStream(const std::string& tag,
                                        RCRTCMediaType type) = 0;

  /**
   * @brief 批量发布指定自定义流
   *
   * @param tags 自定义流的唯一标志列表
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 该接口不关心自定义流的媒体类型，仅关心 tag 是否存在；
   */
  virtual int32_t publishCustomStream(const std::list<std::string>& tags) = 0;

  /**
   * @brief 批量取消发布指定自定义流
   *
   * @param tags 自定义流的唯一标志列表
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 该接口不关心自定义流的媒体类型，仅关心 tag 是否存在；
   */
  virtual int32_t unpublishCustomStream(const std::list<std::string>& tags) = 0;

  /**
   * 利用音频文件发布自定义音频流
   *
   * @param path     文件的绝对路径（带有文件后缀名）
   * @param tag      自定义流的唯一标志
   * @param replace  是否替换默认发送的音频数据
   * @param playback 是否回放音频数据
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   * @remark:        目前仅支持未经编码的 pcm 音频数据
   */
  virtual int32_t publishCustomAudioFromFile(
      const std::string& path,
      const std::string& tag,
      int32_t channel,
      int32_t sample,
      RCRTCAudioSampleFormat format =
          rcrtc::RCRTCAudioSampleFormat::AUDIO_FMT_S16,
      bool playback = false) = 0;

  /**
   * 取消指定自定义音频流
   *
   * @param path     文件的绝对路径（带有文件后缀名）
   * @param tag      自定义流的唯一标志
   * @param replace  是否替换默认发送的音频数据
   * @param playback 是否回放音频数据
   * @return
   */
  virtual int32_t unpublishCustomAudio(const std::string& path,
                                       const std::string& tag) = 0;

  /**
   * @brief 取消远端自定自定义流的渲染
   *
   * @param userId 远端用户Id
   * @param tag 自定义流的唯一标志
   * @param type 自定义流的媒体类型
   * @param mute
   * - true  禁止渲染
   * - false 允许渲染
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark: 只能对已订阅的自定义流设置；
   */
  virtual int32_t muteRemoteCustomStream(const std::string& userId,
                                         const std::string& tag,
                                         RCRTCMediaType type,
                                         bool mute) = 0;

  /**
   * @brief 设置远端自定义视频流设置渲染窗体。
   *
   * @param userId 远端用户ID
   * @param tag 自定义流的唯一标志
   * @param view 渲染窗体
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark:
   * 只能对已存在的自定义流进行配置；远端用户发布的自定义流信息会由回调函数
   * onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished() 通知；
   */
  virtual int32_t setRemoteCustomStreamView(const std::string& userId,
                                            const std::string& tag,
                                            IRCRTCView* view) = 0;

  /**
   * @brief 取消绑定远端发布的自定义视频流渲染窗体。
   *
   * @param userId 远端用户ID
   * @param tag 自定义流的唯一标志
   *
   * @return
   * - 成功返回：0
   * - 失败返回: 非0值，详见错误码
   *
   * @remark:
   * 只能对已存在的自定义流进行配置；远端用户发布的自定义流信息会由回调函数
   * onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished() 通知；
   */
  virtual int32_t removeRemoteCustomStreamView(const std::string& userId,
                                               const std::string& tag) = 0;

  /**
   * @brief 订阅指定用户的指定自定义流
   *
   * @param userId 用户ID
   * @param tag 自定义流唯一标志
   * @param type 媒体类型
   *
   * @return
   * - 成功返回：0
   * - 失败返回：非0值，详见错误码
   *
   * @remark: 远端用户发布的自定义流信息会由回调函数
   *onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished() 通知。
   *	实际的订阅结果需等待 onCustomStreamSubscribed() 函数的回调通知
   */
  virtual int32_t subscribeCustomStream(const std::string& userId,
                                        const std::string& tag,
                                        RCRTCMediaType type) = 0;

  /**
   * @brief 取消订阅指定用户的指定自定义流
   *
   * @param userId 用户ID
   * @param tag 自定义流唯一标志
   * @param type 媒体类型
   *
   * @return
   * - 成功返回：0
   * - 失败返回：非0值，详见错误码
   *
   * @remark: 远端用户发布的自定义流信息会由回调函数
   *onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished() 通知
   *	实际的订阅结果需等待 onCustomStreamUnsubscribed() 函数的回调通知。
   */
  virtual int32_t unsubscribeCustomStream(const std::string& userId,
                                          const std::string& tag,
                                          RCRTCMediaType type) = 0;

  /**
   * @brief 订阅指定用户的的所有自定义流
   *
   * @param userId 用户ID
   * @param tags
   *自定义流唯一标志列表，SDK底层会对该列表进行过滤，仅会订阅已存在自定义流。
   *
   * @return
   * - 成功返回：0
   * - 失败返回：非0值，详见错误码
   *
   * @remark: 远端用户发布的自定义流信息会由回调函数
   *onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished()
   *通知；该接口不关心自定义流的媒体类型。 实际的订阅结果需等待
   *onCustomStreamSubscribed() 函数的回调通知。
   */
  virtual int32_t subscribeCustomStream(const std::string& userId,
                                        const std::list<std::string>& tags) = 0;

  /**
   * @brief 取消订阅指定用户的的所有自定义流
   *
   * @param userId 用户ID
   * @param tag 自定义流唯一标志列表
   *
   * @return
   * - 成功返回：0
   * - 失败返回：非0值，详见错误码
   *
   * @remark: 远端用户发布的自定义流信息会由回调函数
   *onRemoteCustomStreamPublished()和 onRemoteCustomStreamUnpublished() 通知；
   *  该接口不关心自定义流的媒体类型。
   *	实际的订阅结果需等待 onCustomStreamUnsubscribed() 函数的回调通知。
   */
  virtual int32_t unsubscribeCustomStream(
      const std::string& userId,
      const std::list<std::string>& tags) = 0;

  // 合流相关 操作接口
  virtual int32_t addLiveCdn(const std::string& url) = 0;
  virtual int32_t removeLiveCdn(const std::string& url) = 0;

  /**
   * 设置合流布局模式
   *
   * @param mode 合流布局模式
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixLayoutMode(RCRTCLiveMixLayoutMode mode) = 0;

  /**
   * 设置合流渲染模式
   *
   * @param mode 合流渲染模式
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixRenderMode(RCRTCLiveMixRenderMode mode) = 0;

  /**
   * 设置合流自定义布局
   *
   * @param layouts 合流自定义布局
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixCustomLayouts(
      const std::list<RCRTCCustomLayout>& layouts) = 0;

  /**
   * 设置合流中参与混音的主播
   *
   * @param userIds 合流中参与混音的主播, mixAll 为 false 时有效
   * @param mixAll true: 所有主播参与混音
   *               false: 只有 userIds 中的主播参与混音
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixCustomAudios(const std::list<std::string>& userIds,
                                         bool mixAll) = 0;

  /**
   * 设置合流中音频输出码率
   *
   * @param bitrate 合流中音频输出码率
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixAudioBitrate(int32_t bitrate) = 0;

  /**
   * 设置合流中视频输出码率
   *
   * @param bitrate 合流中视频输出码率
   * @param tiny 是否是小流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixVideoBitrate(int32_t bitrate, bool tiny) = 0;

  /**
   * 设置合流中视频输出分辨率
   *
   * @param resolution 合流中视频输出分辨率
   * @param tiny 是否是小流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixVideoResolution(RCRTCVideoResolution resolution,
                                            bool tiny) = 0;
  /**
   * 设置合流画面背景颜色
   *
   * @param color 16进制的颜色值
   *
   * @return 0: 成功, 非0: 失败
   *
   * @remark: 格式为 RGB 定义下的 Hex 值，不要带 # 号，如 0xFFB6C1
   * 表示浅粉色。默认0x000000，黑色。取值范围 [0x000000, 0xFFFFFF]
   */
  virtual int32_t setLiveMixBackgroundColor(int32_t color) = 0;

  /**
   * 设置合流画面背景颜色
   *
   * @param red   RGB 红色分量, 取值范围: 0 ~ 255
   * @param green RGB 绿色分量, 取值范围: 0 ~ 255
   * @param blue  RGB 蓝色分量, 取值范围: 0 ~ 255
   *
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixBackgroundColor(int32_t red,
                                            int32_t green,
                                            int32_t blue) = 0;

  /**
   * 设置合流中视频输出帧率
   *
   * @param bitrate 合流中视频输出帧率
   * @param tiny 是否是小流
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t setLiveMixVideoFps(RCRTCVideoFps fps, bool tiny) = 0;

  // 音效
  virtual int32_t createAudioEffect(const std::string& file_path,
                                    int32_t effectId) = 0;
  virtual int32_t releaseAudioEffect(int32_t effectId) = 0;
  virtual int32_t playAudioEffect(int32_t effectId,
                                  uint32_t volume,
                                  int32_t loop) = 0;
  virtual int32_t pauseAudioEffect(int32_t effectId) = 0;
  virtual int32_t pauseAllAudioEffects() = 0;
  virtual int32_t resumeAudioEffect(int32_t effectId) = 0;
  virtual int32_t resumeAllAudioEffects() = 0;
  virtual int32_t stopAudioEffect(int32_t effectId) = 0;
  virtual int32_t stopAllAudioEffects() = 0;
  virtual int32_t adjustAudioEffectVolume(int32_t effectId,
                                          uint32_t volume) = 0;
  virtual int32_t getAudioEffectVolume(int32_t effectId) = 0;
  virtual int32_t adjustAllAudioEffectsVolume(uint32_t volume) = 0;
  virtual int32_t getAllAudioEffectsVolume() = 0;

  // 混音
  virtual int32_t startAudioMixing(const std::string& file_path,
                                   RCRTCAudioMixingMode mode,
                                   bool playback,
                                   int32_t loop) = 0;
  virtual int32_t stopAudioMixing() = 0;
  virtual int32_t pauseAudioMixing() = 0;
  virtual int32_t resumeAudioMixing() = 0;
  virtual int32_t adjustAudioMixingVolume(uint32_t volume) = 0;
  virtual int32_t adjustAudioMixingPlaybackVolume(uint32_t volume) = 0;
  virtual int32_t adjustAudioMixingPublishVolume(uint32_t volume) = 0;
  virtual int32_t getAudioMixingPlaybackVolume() = 0;
  virtual int32_t getAudioMixingPublishVolume() = 0;
  virtual int32_t setAudioMixingPosition(double position) = 0;
  virtual double getAudioMixingPosition() = 0;
  virtual int32_t getAudioMixingDuration() = 0;  // 秒

  // 音频处理
  virtual int32_t setLocalAudioCapturedListener(
      RCRTCWritableAudioFrameListener* listener) = 0;
  virtual int32_t setLocalAudioMixedListener(
      RCRTCWritableAudioFrameListener* listener) = 0;
  virtual int32_t setRemoteAudioReceivedListener(
      const std::string& user_id,
      RCRTCReadableAudioFrameListener* listener) = 0;
  virtual int32_t setRemoteAudioMixedListener(
      RCRTCReadableAudioFrameListener* listener) = 0;

  virtual int32_t setLocalVideoProcessedListener(
      RCRTCWritableVideoFrameListener* listener) = 0;
  virtual int32_t setRemoteVideoProcessedListener(
      const std::string& user_id,
      RCRTCReadableVideoFrameListener* listener) = 0;
  virtual int32_t setLocalCustomVideoProcessedListener(
      const std::string& tag,
      RCRTCWritableVideoFrameListener* listener) = 0;
  virtual int32_t setRemoteCustomVideoProcessedListener(
      const std::string& user_id,
      const std::string& tag,
      RCRTCReadableVideoFrameListener* listener) = 0;

  /**
   * 切换角色
   *
   * @param role 切换后的角色
   * @return 0: 成功, 非0: 失败
   */
  virtual int32_t switchLiveRole(RCRTCRole role) = 0;
};

}  // namespace rcrtc

#endif
