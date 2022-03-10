#include "rcrtc_listener_impl.h"
#include <QDebug>

#include "utility.h"
using namespace rcrtc;

RcRtcListenerImpl::RcRtcListenerImpl(QObject* parent) : QObject(parent) {}

RcRtcListenerImpl::~RcRtcListenerImpl() {}

void RcRtcListenerImpl::onJoinedRoomGot(const std::list<rcrtc::RCRTCUserJoinedRoom>& roomInfo,
                             int32_t code){

}

void RcRtcListenerImpl::onRoomJoined(int code, const std::string& errMsg) {
  QString strErrMsg = ConvertToQString(errMsg);
  qInfo() << "onRoomJoined, code:" << code << ", errmsg:" << strErrMsg;
  Q_EMIT RoomJoinedSignal(code);
}

void RcRtcListenerImpl::onRoomLeft(int code, const std::string& errMsg) {
    QString strErrMsg = ConvertToQString(errMsg);
    qInfo() << "onRoomLeft, code:" << code << ", errmsg:" << strErrMsg;
  Q_EMIT RoomLeftSignal(code);
}

void RcRtcListenerImpl::onError(int code) {
  qInfo("onError(%d)", code);
  Q_EMIT RoomLeftSignal(code);
}

void RcRtcListenerImpl::onKicked(const std::string& roomId,
                                 const std::string& errMsg) {
  QString strRoomId = ConvertToQString(roomId);
  QString strErrMsg = ConvertToQString(errMsg);
  qInfo() << "onKicked, roomid:" << strRoomId << ", errmsg:" << strErrMsg;
  Q_EMIT RoomKickedSignal(strRoomId, strErrMsg);
}

void RcRtcListenerImpl::onUserJoined(const std::string& userId) {
  QString strUserId = ConvertToQString(userId);
  qInfo() << "onUserJoined, userId:" << strUserId;
  Q_EMIT UserJoinedSignal(strUserId);
}

void RcRtcListenerImpl::onUserOffline(const std::string& userId) {
  QString strUserId = ConvertToQString(userId);
  qInfo() << "onUserOffline, userId:" << strUserId;
  Q_EMIT UserOfflineSignal(strUserId);
}

void RcRtcListenerImpl::onUserLeft(const std::string& userId) {
  QString strUserId = ConvertToQString(userId);
  qInfo() << "onUserLeft, userId:" << strUserId;
  Q_EMIT UserLeftSignal(strUserId);
}

void RcRtcListenerImpl::onRemotePublished(const std::string& userId,
                                          RCRTCMediaType type) {
  QString strUserId =  ConvertToQString(userId);
  qInfo() << "onRemotePublished, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type);
  Q_EMIT RemotePublishedSignal(strUserId, type);
}

void RcRtcListenerImpl::onRemoteUnpublished(const std::string& userId,
                                            RCRTCMediaType type) {
  QString strUserId =  ConvertToQString(userId);
  qInfo() << "onRemoteUnpublished, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type);
  Q_EMIT RemoteUnpublishedSignal(strUserId, type);
}

void RcRtcListenerImpl::onRemoteStateChanged(const std::string& userId,
                                             RCRTCMediaType type,
                                             bool disabled) {
  QString strUserId =  ConvertToQString(userId);
  qInfo() << "onRemoteStateChanged, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type)
          << ", disabled:" << disabled;
  Q_EMIT RemoteStateChangedSignal(strUserId, type, disabled);
}

void RcRtcListenerImpl::onRemoteFirstFrame(const std::string& userId,
                                           RCRTCMediaType type) {
  QString strUserId = ConvertToQString(userId);
  qInfo() << "onRemoteFirstFrame, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type);
  Q_EMIT RemoteFirstFrameSignal(strUserId, type);
}

void RcRtcListenerImpl::onRemoteLiveMixPublished(RCRTCMediaType type) {
  qInfo() << "onRemoteLiveMixPublished, RCRTCMediaType:"
          << static_cast<int>(type);
  Q_EMIT RemoteLiveMixPublishedSignal(type);
}

void RcRtcListenerImpl::onRemoteLiveMixUnpublished(RCRTCMediaType type) {
  qInfo() << "onRemoteLiveMixUnpublished, RCRTCMediaType:"
          << static_cast<int>(type);
  Q_EMIT RemoteLiveMixUnpublishedSignal(type);
}

void RcRtcListenerImpl::onRemoteLiveMixFirstFrame(RCRTCMediaType type) {
  qInfo() << "onRemoteLiveMixFirstFrame, RCRTCMediaType:"
          << static_cast<int>(type);
  Q_EMIT RemoteLiveMixFirstFrameSignal(type);
}

void RcRtcListenerImpl::onPublished(RCRTCMediaType type, int code, const std::string& errMsg) {
  QString msg =  ConvertToQString(errMsg);
  qInfo() << "onPublished, RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code
          << ", msg:" << msg;
  Q_EMIT PublishedSignal(type, code);
}

void RcRtcListenerImpl::onUnpublished(RCRTCMediaType type, int code, const std::string& errMsg) {
  QString msg =  ConvertToQString(errMsg);
  qInfo() << "onUnpublished, RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code
          << ", msg:" << msg;
  Q_EMIT UnpublishedSignal(type, code);
}

void RcRtcListenerImpl::onSubscribed(const std::string& userId,
                                     RCRTCMediaType type,
                                     int code,
                                     const std::string& errMsg) {
  QString strUserId =  ConvertToQString(userId);
  QString msg =  ConvertToQString(errMsg);
  qInfo() << "onSubscribed, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code
          << ", msg:" << msg;
  Q_EMIT SubscribedSignal(strUserId, type, code);
}

void RcRtcListenerImpl::onUnsubscribed(const std::string& userId,
                                       RCRTCMediaType type,
                                       int code,
                                       const std::string& errMsg) {
  QString strUserId =  ConvertToQString(userId);
  QString msg =  ConvertToQString(errMsg);
  qInfo() << "onUnsubscribed, userId:" << strUserId
          << " , RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code
          << ", msg:" << msg;
  Q_EMIT UnsubscribedSignal(strUserId, type, code);
}

void RcRtcListenerImpl::onLiveMixSubscribed(rcrtc::RCRTCMediaType type,
                                            int code,
                                            const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixSubscribed, RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixSubscribedSignal(type, code, msg);
}

void RcRtcListenerImpl::onLiveMixUnsubscribed(rcrtc::RCRTCMediaType type,
                                              int code,
                                              const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixUnsubscribed, RCRTCMediaType:" << static_cast<int>(type)
          << ", code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixUnsubscribedSignal(type, code, msg);
}

void RcRtcListenerImpl::onEnableCamera(bool enable,
                                       int code,
                                       const std::string& errMsg) {
  QString msg =  ConvertToQString(errMsg);
  qInfo() << "onEnableCamera, enable:" << enable << ", code:" << code
          << ", errMsg:" << msg;
  Q_EMIT EnableCameraSignal(enable, code, msg);
}

void RcRtcListenerImpl::onSwitchCamera(const rcrtc::RCRTCCamera* camera,
                                       int code,
                                       const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onSwitchCamera, code:" << code << ", errMsg:" << msg;
  // Q_EMIT EnableCameraSignal(enable, code, msg);
}

void RcRtcListenerImpl::onLiveCdnAdded(const std::string& url,
                                       int code,
                                       const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  QString qsUrl = ConvertToQString(url);
  qInfo() << "onLiveCdnAdded, url:" << qsUrl << ", code:" << code
          << ", errMsg:" << msg;
  Q_EMIT LiveCdnAddedSignal(qsUrl, code, msg);
}

void RcRtcListenerImpl::onLiveCdnRemoved(const std::string& url,
                                         int code,
                                         const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  QString qsUrl = ConvertToQString(url);
  qInfo() << "onLiveCdnRemoved, url:" << qsUrl << ", code:" << code
          << ", errMsg:" << msg;
  Q_EMIT LiveCdnRemovedSignal(qsUrl, code, msg);
}

void RcRtcListenerImpl::onLiveMixLayoutModeSet(int code,
                                               const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixLayoutModeSet, code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixLayoutModeSetSignal(code, msg);
}

void RcRtcListenerImpl::onLiveMixRenderModeSet(int code,
                                               const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixRenderModeSet, code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixRenderModeSetSignal(code, msg);
}

void RcRtcListenerImpl::onLiveMixCustomLayoutsSet(int code,
                                                  const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixCustomLayoutsSet, code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixCustomLayoutsSetSignal(code, msg);
}

void RcRtcListenerImpl::onLiveMixCustomAudiosSet(int code,
                                                 const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixCustomAudiosSet, code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixCustomAudiosSetSignal(code, msg);
}

void RcRtcListenerImpl::onLiveMixAudioBitrateSet(int code,
                                                 const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixAudioBitrateSet, code:" << code << ", errMsg:" << msg;
  Q_EMIT LiveMixAudioBitrateSetSignal(code, msg);
}

void RcRtcListenerImpl::onLiveMixVideoBitrateSet(bool tiny,
                                                 int code,
                                                 const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixVideoBitrateSet, tiny:" << tiny << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT LiveMixVideoBitrateSetSignal(tiny, code, msg);
}

void RcRtcListenerImpl::onLiveMixVideoResolutionSet(bool tiny,
                                                    int code,
                                                    const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixVideoResolutionSet, tiny:" << tiny << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT LiveMixVideoResolutionSetSignal(tiny, code, msg);
}

void RcRtcListenerImpl::onLiveMixVideoFpsSet(bool tiny,
                                             int code,
                                             const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveMixVideoFpsSet, tiny:" << tiny << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT LiveMixVideoFpsSetSignal(tiny, code, msg);
}

void RcRtcListenerImpl::onLiveMixBackgroundColorSet(int32_t code, const std::string &errMsg)
{
    QString msg = ConvertToQString(errMsg);
    qInfo() << "onLiveMixBackgroundColorSet, code:" << code
            << ", errMsg : " << msg;
    Q_EMIT LiveMixBackgroundColorSet(code, msg);
}

void RcRtcListenerImpl::onAudioEffectCreated(int effectId,
                                             int code,
                                             const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onAudioEffectCreated, effectId:" << effectId << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT AudioEffectCreatedSignal(effectId, code, msg);
}

void RcRtcListenerImpl::onAudioEffectFinished(int effectId) {
  qInfo() << "onAudioEffectFinished, effectId:" << effectId;
  Q_EMIT AudioEffectFinishedSignal(effectId);
}

void RcRtcListenerImpl::onAudioMixingStarted() {
  qInfo() << "onAudioMixingStarted IN!";
  Q_EMIT AudioMixingStartedSignal();
}

void RcRtcListenerImpl::onAudioMixingPaused() {
  qInfo() << "onAudioMixingPaused IN!";
  Q_EMIT AudioMixingPausedSignal();
}

void RcRtcListenerImpl::onAudioMixingStopped() {
  qInfo() << "onAudioMixingStopped IN!";
  Q_EMIT AudioMixingStoppedSignal();
}

void RcRtcListenerImpl::onAudioMixingFinished() {
  qInfo() << "onAudioMixingFinished IN!";
  Q_EMIT AudioMixingFinishedSignal();
}

void RcRtcListenerImpl::onCustomStreamPublished(const std::string& tag,
                                                rcrtc::RCRTCMediaType type,
                                                int code,
                                                const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  QString stream_tag = ConvertToQString(tag);
  qInfo() << "onCustomStreamPublished, tag:" << stream_tag
          << ", type:" << static_cast<int>(type) << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT CustomStreamPublishedSignal(stream_tag, type, code, msg);
}

void RcRtcListenerImpl::onCustomStreamUnpublished(const std::string& tag,
                                                  rcrtc::RCRTCMediaType type,
                                                  int code,
                                                  const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  QString stream_tag =ConvertToQString(tag);
  qInfo() << "onCustomStreamUnpublished, tag:" << stream_tag
          << ", type:" << static_cast<int>(type) << ", code:" << code
          << ", errMsg : " << msg;
  Q_EMIT CustomStreamUnpublishedSignal(stream_tag, type, code, msg);
}

void RcRtcListenerImpl::onCustomStreamPublishFinished(
    const std::string& tag,
    rcrtc::RCRTCMediaType type) {}

void RcRtcListenerImpl::onCustomStreamPublished(
    const std::list<std::string>& tags,
    int code,
    const std::string& errMsg) {
  QList<QString> stream_tags;
  for (const auto& it : tags) {
    QString tag = ConvertToQString(it);
    stream_tags.push_back(tag);
  }
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onCustomStreamPublished, tag size:" << stream_tags.size()
          << ", code:" << code << ", errMsg : " << msg;
  Q_EMIT CustomStreamPublishedListSignal(stream_tags, code, msg);
}

void RcRtcListenerImpl::onCustomStreamUnpublished(
    const std::list<std::string>& tags,
    int code,
    const std::string& errMsg) {
  QList<QString> stream_tags;
  for (const auto& it : tags) {
    QString tag = ConvertToQString(it);
    stream_tags.push_back(tag);
  }
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onCustomStreamUnpublished, tag size:" << stream_tags.size()
          << ", code:" << code << ", errMsg : " << msg;
  Q_EMIT CustomStreamUnpublishedListSignal(stream_tags, code, msg);
}

void RcRtcListenerImpl::onCustomStreamPublishFinished(
    const std::list<std::string>& tags) {}

void RcRtcListenerImpl::onRemoteCustomStreamPublished(
    const std::string& userId,
    const std::string& tag,
    rcrtc::RCRTCMediaType type) {
  QString user_id = ConvertToQString(userId);
  QString stream_tag = ConvertToQString(tag);
  qInfo() << "onRemoteCustomStreamPublished, user_id:" << user_id
          << ", stream_tag:" << stream_tag
          << ", RCRTCMediaType : " << static_cast<int>(type);
  Q_EMIT RemoteCustomStreamPublishedSignal(user_id, stream_tag, type);
}

void RcRtcListenerImpl::onRemoteCustomStreamUnpublished(
    const std::string& userId,
    const std::string& tag,
    rcrtc::RCRTCMediaType type) {
  QString user_id = ConvertToQString(userId);
  QString stream_tag = ConvertToQString(tag);
  qInfo() << "onRemoteCustomStreamUnpublished, user_id:" << user_id
          << ", stream_tag:" << stream_tag
          << ", RCRTCMediaType : " << static_cast<int>(type);
  Q_EMIT RemoteCustomStreamUnpublishedSignal(user_id, stream_tag, type);
}

void RcRtcListenerImpl::onRemoteCustomStreamStateChanged(
    const std::string& userId,
    const std::string& tag,
    rcrtc::RCRTCMediaType type,
    bool disabled) {
    QString user_id = ConvertToQString(userId);
    QString stream_tag = ConvertToQString(tag);
    qInfo() << "onRemoteCustomStreamStateChanged, user_id:" << user_id
            << ", stream_tag:" << stream_tag
            << ", RCRTCMediaType : " << static_cast<int>(type);
    Q_EMIT RemoteCustomStreamStateChangedSignal(user_id, stream_tag, type, disabled);
}

void RcRtcListenerImpl::onRemoteCustomStreamFirstFrame(
    const std::string& userId,
    const std::string& tag,
    rcrtc::RCRTCMediaType type) {
  QString user_id = ConvertToQString(userId);
  QString stream_tag = ConvertToQString(tag);
  qInfo() << "onRemoteCustomStreamFirstFrame, user_id:" << user_id
          << ", stream_tag:" << stream_tag
          << ", RCRTCMediaType : " << static_cast<int>(type);
  Q_EMIT RemoteCustomStreamFirstFrameSignal(user_id, stream_tag, type);
}

void RcRtcListenerImpl::onCustomStreamSubscribed(const std::string& userId,
                                                 const std::string& tag,
                                                 rcrtc::RCRTCMediaType type,
                                                 int code,
                                                 const std::string& errMsg) {
  QString user_id = ConvertToQString(userId);
  QString stream_tag = ConvertToQString(tag);
  QString msg = QString::fromUtf8(
      QByteArray::fromRawData(errMsg.c_str(), (int)errMsg.size()));
  qInfo() << "onCustomStreamSubscribed, user_id:" << user_id
          << ", stream_tag:" << stream_tag
          << ", RCRTCMediaType : " << static_cast<int>(type)
          << ", msg : " << msg;
  Q_EMIT CustomStreamSubscribedSignal(user_id, stream_tag, type, code, msg);
}

void RcRtcListenerImpl::onCustomStreamUnsubscribed(const std::string& userId,
                                                   const std::string& tag,
                                                   rcrtc::RCRTCMediaType type,
                                                   int code,
                                                   const std::string& errMsg) {
  QString user_id = ConvertToQString(userId);
  QString stream_tag = ConvertToQString(tag);
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onCustomStreamUnsubscribed, user_id:" << user_id
          << ", stream_tag:" << stream_tag
          << ", RCRTCMediaType : " << static_cast<int>(type)
          << ", msg : " << msg;
  Q_EMIT CustomStreamUnsubscribedSignal(user_id, stream_tag, type, code, msg);
}

void RcRtcListenerImpl::onCustomStreamSubscribed(
    const std::string& userId,
    const std::list<std::string>& tags,
    int code,
    const std::string& errMsg) {}

void RcRtcListenerImpl::onCustomStreamUnsubscribed(
    const std::string& userId,
    const std::list<std::string>& tags,
    int code,
    const std::string& errMsg) {}

void RcRtcListenerImpl::onLiveRoleSwitched(rcrtc::RCRTCRole curRole,
                                           int code,
                                           const std::string& errMsg) {
  QString msg = ConvertToQString(errMsg);
  qInfo() << "onLiveRoleSwitched, curRole:" << static_cast<int32_t>(curRole)
          << ", code:" << code << ", errMsg : " << msg;
  Q_EMIT LiveRoleSwitchedSignal(curRole, code, msg);
}

void RcRtcListenerImpl::onRemoteLiveRoleSwitched(const std::string& roomId,
                                                 const std::string& userId,
                                                 rcrtc::RCRTCRole role) {
  QString room_id = ConvertToQString(roomId);
  QString user_id = ConvertToQString(userId);
  qInfo() << "onRemoteLiveRoleSwitched, curRole:" << static_cast<int32_t>(role)
          << ", roomId:" << room_id << ", userId : " << user_id;
  Q_EMIT RemoteLiveRoleSwitchedSignal(room_id, user_id, role);
}
