#ifndef RCRTCLISTENERIMPL_H
#define RCRTCLISTENERIMPL_H

#include <QObject>
#include "rcrtc_listener.h"

class RcRtcListenerImpl : public QObject, public rcrtc::IRCRTCListener {
  Q_OBJECT
 public:
  explicit RcRtcListenerImpl(QObject* parent = nullptr);
  ~RcRtcListenerImpl();

 Q_SIGNALS:
  void RoomJoinedSignal(int code);
  void RoomLeftSignal(int code);
  void RoomErrorSignal(int code);
  void RoomKickedSignal(QString roomId, QString errMsg);
  void UserJoinedSignal(QString userId);
  void UserOfflineSignal(QString userId);
  void UserLeftSignal(QString userId);
  void RemotePublishedSignal(QString userId, rcrtc::RCRTCMediaType type);
  void RemoteUnpublishedSignal(QString userId, rcrtc::RCRTCMediaType type);
  void RemoteStateChangedSignal(QString userId,
                                rcrtc::RCRTCMediaType type,
                                bool disabled);
  void RemoteFirstFrameSignal(QString userId, rcrtc::RCRTCMediaType type);
  void RemoteLiveMixPublishedSignal(rcrtc::RCRTCMediaType type);
  void RemoteLiveMixUnpublishedSignal(rcrtc::RCRTCMediaType type);
  void RemoteLiveMixFirstFrameSignal(rcrtc::RCRTCMediaType type);
  void PublishedSignal(rcrtc::RCRTCMediaType type, int code);
  void UnpublishedSignal(rcrtc::RCRTCMediaType type, int code);
  void SubscribedSignal(QString userId, rcrtc::RCRTCMediaType type, int code);
  void UnsubscribedSignal(QString userId, rcrtc::RCRTCMediaType type, int code);
  void LiveMixSubscribedSignal(rcrtc::RCRTCMediaType type,
                               int code,
                               QString errMsg);
  void LiveMixUnsubscribedSignal(rcrtc::RCRTCMediaType type,
                                 int code,
                                 QString errMsg);
  void EnableCameraSignal(bool enable, int code, QString errMsg);
  void SwitchCameraSignal(const rcrtc::RCRTCCamera* camera,
                          int code,
                          QString errMsg);
  void LiveCdnAddedSignal(QString url, int code, QString errMsg);
  void LiveCdnRemovedSignal(QString url, int code, QString errMsg);
  void LiveMixLayoutModeSetSignal(int code, QString errMsg);
  void LiveMixRenderModeSetSignal(int code, QString errMsg);
  void LiveMixCustomLayoutsSetSignal(int code, QString errMsg);
  void LiveMixCustomAudiosSetSignal(int code, QString errMsg);
  void LiveMixAudioBitrateSetSignal(int code, QString errMsg);
  void LiveMixVideoBitrateSetSignal(bool tiny, int code, QString errMsg);
  void LiveMixVideoResolutionSetSignal(bool tiny, int code, QString errMsg);
  void LiveMixVideoFpsSetSignal(bool tiny, int code, QString errMsg);
  void LiveMixBackgroundColorSet(int32_t code,QString errMsg);
  void AudioEffectCreatedSignal(int effectId, int code, QString errMsg);
  void AudioEffectFinishedSignal(int effectId);
  void AudioMixingStartedSignal();
  void AudioMixingPausedSignal();
  void AudioMixingStoppedSignal();
  void AudioMixingFinishedSignal();

  void CustomStreamPublishedSignal(QString tag,
                                   rcrtc::RCRTCMediaType type,
                                   int code,
                                   QString errMsg);

  void CustomStreamUnpublishedSignal(QString tag,
                                     rcrtc::RCRTCMediaType type,
                                     int code,
                                     QString errMsg);

  void CustomStreamPublishFinishedSignal(QString tag,
                                         rcrtc::RCRTCMediaType type);

  void CustomStreamPublishedListSignal(QList<QString> tags,
                                       int code,
                                       QString errMsg);

  void CustomStreamUnpublishedListSignal(QList<QString> tags,
                                         int code,
                                         QString errMsg);

  void CustomStreamPublishFinishedSignal(QList<QString> tags);

  void RemoteCustomStreamPublishedSignal(QString userId,
                                         QString tag,
                                         rcrtc::RCRTCMediaType type);

  void RemoteCustomStreamUnpublishedSignal(QString userId,
                                           QString tag,
                                           rcrtc::RCRTCMediaType type);

  void RemoteCustomStreamStateChangedSignal(QString userId,
                                            QString tag,
                                            rcrtc::RCRTCMediaType type,
                                            bool disabled);

  void RemoteCustomStreamFirstFrameSignal(QString userId,
                                          QString tag,
                                          rcrtc::RCRTCMediaType type);
  void CustomStreamSubscribedSignal(QString userId,
                                    QString tag,
                                    rcrtc::RCRTCMediaType type,
                                    int code,
                                    QString errMsg);

  void CustomStreamUnsubscribedSignal(QString userId,
                                      QString tag,
                                      rcrtc::RCRTCMediaType type,
                                      int code,
                                      QString errMsg);

  void CustomStreamListSubscribedSignal(QString userId,
                                        QList<QString> tags,
                                        int code,
                                        QString errMsg);

  void CustomStreamListUnsubscribedSignal(QString userId,
                                          QList<QString> tags,
                                          int code,
                                          QString errMsg);

  void LiveRoleSwitchedSignal(rcrtc::RCRTCRole curRole,
                              int code,
                              QString errMsg);

  void RemoteLiveRoleSwitchedSignal(QString roomId,
                                    QString userId,
                                    rcrtc::RCRTCRole role);

 public:

  virtual void onJoinedRoomGot(const std::list<rcrtc::RCRTCUserJoinedRoom>& roomInfo,
                               int32_t code) override;
  /**
   * 本地用户加入房间回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onRoomJoined(int code, const std::string& errMsg) override;

  /**
   * 本地用户离开房间回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onRoomLeft(int code, const std::string& errMsg) override;

  /**
   * 引擎内部错误回调
   *
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onError(int code) override;

  /**
   * 本地用户被踢出房间回调
   *
   * @param roomId 房间 id
   * @param errMsg 失败原因
   */
  virtual void onKicked(const std::string& roomId,
                        const std::string& errMsg) override;

  /**
   * 远端用户加入房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserJoined(const std::string& userId) override;

  /**
   * 远端用户因离线离开房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserOffline(const std::string& userId) override;

  /**
   * 远端用户离开房间操作回调
   *
   * @param userId 用户 id
   */
  virtual void onUserLeft(const std::string& userId) override;

  /**
   * 远端用户发布资源操作回调
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   */
  virtual void onRemotePublished(const std::string& userId,
                                 rcrtc::RCRTCMediaType type) override;

  /**
   * 远端用户取消发布资源操作回调
   *
   * @param userId 远端用户 UserId
   * @param type   资源类型
   */
  virtual void onRemoteUnpublished(const std::string& userId,
                                   rcrtc::RCRTCMediaType type) override;

  /**
   * 远端用户资源状态操作回调
   *
   * @param userId   远端用户UserId
   * @param type     资源类型
   * @param disabled 是否停止相应资源采集
   */
  virtual void onRemoteStateChanged(const std::string& userId,
                                    rcrtc::RCRTCMediaType type,
                                    bool disabled) override;

  /**
   * 收到远端用户第一帧数据
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   */
  virtual void onRemoteFirstFrame(const std::string& userId,
                                  rcrtc::RCRTCMediaType type) override;

  /**
   * 远端直播合流发布资源操作回调
   *
   * @param type   资源类型
   */
  virtual void onRemoteLiveMixPublished(rcrtc::RCRTCMediaType type) override;

  /**
   * 远端直播合流取消发布资源操作回调
   *
   * @param type   资源类型
   */
  virtual void onRemoteLiveMixUnpublished(rcrtc::RCRTCMediaType type) override;
  /**
   * 收到直播合流第一帧数据
   *
   * @param type 资源类型
   */
  virtual void onRemoteLiveMixFirstFrame(rcrtc::RCRTCMediaType type) override;

  /**
   * 本地用户发布资源回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onPublished(rcrtc::RCRTCMediaType type, int code, const std::string& errMsg) override;

  /**
   * 本地用户取消发布资源回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onUnpublished(rcrtc::RCRTCMediaType type, int code, const std::string& errMsg) override;

  /**
   * 订阅远端用户发布的资源操作回调
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onSubscribed(const std::string& userId,
                            rcrtc::RCRTCMediaType type,
                            int code,
                            const std::string& errMsg) override;

  /**
   * 取消订阅远端用户发布的资源操作回调
   *
   * @param userId 远端用户UserId
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   */
  virtual void onUnsubscribed(const std::string& userId,
                              rcrtc::RCRTCMediaType type,
                              int code,
                              const std::string& errMsg) override;

  /**
   * 订阅合流资源操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixSubscribed(rcrtc::RCRTCMediaType type,
                                   int code,
                                   const std::string& errMsg) override;

  /**
   * 取消订阅合流资源操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onLiveMixUnsubscribed(rcrtc::RCRTCMediaType type,
                                     int code,
                                     const std::string& errMsg) override;

  /**
   * 使能摄像头操作回调
   *
   * @param type   资源类型
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg  错误描述
   */
  virtual void onEnableCamera(bool enable,
                              int code,
                              const std::string& errMsg) override;

  /**
   * 切换摄像头操作回调
   *
   * @param camera 摄像头信息（函数调用结束，指针即刻销毁）
   * @param code   0: 调用成功, 非0: 失败
   * @param errMsg 错误描述
   */
  virtual void onSwitchCamera(const rcrtc::RCRTCCamera* camera,
                              int code,
                              const std::string& errMsg) override;

  virtual void onLiveCdnAdded(const std::string& url,
                              int code,
                              const std::string& errMsg) override;
  virtual void onLiveCdnRemoved(const std::string& url,
                                int code,
                                const std::string& errMsg) override;

  virtual void onLiveMixLayoutModeSet(int code,
                                      const std::string& errMsg) override;

  virtual void onLiveMixRenderModeSet(int code,
                                      const std::string& errMsg) override;

  virtual void onLiveMixCustomLayoutsSet(int code,
                                         const std::string& errMsg) override;

  virtual void onLiveMixCustomAudiosSet(int code,
                                        const std::string& errMsg) override;

  virtual void onLiveMixAudioBitrateSet(int code,
                                        const std::string& errMsg) override;

  virtual void onLiveMixVideoBitrateSet(bool tiny,
                                        int code,
                                        const std::string& errMsg) override;

  virtual void onLiveMixVideoResolutionSet(bool tiny,
                                           int code,
                                           const std::string& errMsg) override;

  virtual void onLiveMixVideoFpsSet(bool tiny,
                                    int code,
                                    const std::string& errMsg) override;

  virtual void onLiveMixBackgroundColorSet(int32_t code,
                                           const std::string& errMsg) override;

  virtual void onAudioEffectCreated(int effectId,
                                    int code,
                                    const std::string& errMsg) override;

  virtual void onAudioEffectFinished(int effectId) override;

  virtual void onAudioMixingStarted() override;

  virtual void onAudioMixingPaused() override;

  virtual void onAudioMixingStopped() override;

  virtual void onAudioMixingFinished() override;

  virtual void onCustomStreamPublished(const std::string& tag,
                                       rcrtc::RCRTCMediaType type,
                                       int code,
                                       const std::string& errMsg) override;

  virtual void onCustomStreamUnpublished(const std::string& tag,
                                         rcrtc::RCRTCMediaType type,
                                         int code,
                                         const std::string& errMsg) override;

  virtual void onCustomStreamPublishFinished(
      const std::string& tag,
      rcrtc::RCRTCMediaType type) override;

  virtual void onCustomStreamPublished(const std::list<std::string>& tags,
                                       int code,
                                       const std::string& errMsg) override;

  virtual void onCustomStreamUnpublished(const std::list<std::string>& tags,
                                         int code,
                                         const std::string& errMsg) override;

  virtual void onCustomStreamPublishFinished(
      const std::list<std::string>& tags) override;

  virtual void onRemoteCustomStreamPublished(
      const std::string& userId,
      const std::string& tag,
      rcrtc::RCRTCMediaType type) override;

  virtual void onRemoteCustomStreamUnpublished(
      const std::string& userId,
      const std::string& tag,
      rcrtc::RCRTCMediaType type) override;

  virtual void onRemoteCustomStreamStateChanged(const std::string& userId,
                                                const std::string& tag,
                                                rcrtc::RCRTCMediaType type,
                                                bool disabled) override;

  virtual void onRemoteCustomStreamFirstFrame(
      const std::string& userId,
      const std::string& tag,
      rcrtc::RCRTCMediaType type) override;

  virtual void onCustomStreamSubscribed(const std::string& userId,
                                        const std::string& tag,
                                        rcrtc::RCRTCMediaType type,
                                        int code,
                                        const std::string& errMsg) override;

  virtual void onCustomStreamUnsubscribed(const std::string& userId,
                                          const std::string& tag,
                                          rcrtc::RCRTCMediaType type,
                                          int code,
                                          const std::string& errMsg) override;

  virtual void onCustomStreamSubscribed(const std::string& userId,
                                        const std::list<std::string>& tags,
                                        int code,
                                        const std::string& errMsg) override;

  virtual void onCustomStreamUnsubscribed(const std::string& userId,
                                          const std::list<std::string>& tags,
                                          int code,
                                          const std::string& errMsg) override;

  virtual void onLiveRoleSwitched(rcrtc::RCRTCRole curRole,
                                  int code,
                                  const std::string& errMsg) override;

  virtual void onRemoteLiveRoleSwitched(const std::string& roomId,
                                        const std::string& userId,
                                        rcrtc::RCRTCRole role) override;
};

#endif  // RCRTCLISTENERIMPL_H
