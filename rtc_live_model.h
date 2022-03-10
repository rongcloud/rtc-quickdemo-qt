#ifndef RTC_LIVE_MODEL_H
#define RTC_LIVE_MODEL_H

#include "rcrtc_constants.h"
#include "rcrtc_engine.h"
#include "rcrtc_room_setup.h"
#include "rtc_constants.h"

#include <QWidget>
#include <QReadWriteLock>


namespace Ui {
class RtcLiveModel;
}
class RcRtcListenerImpl;
class RtcVideoRender;
struct RemoteMediaInfo;

class RtcLiveModel : public QWidget
{
    Q_OBJECT

Q_SIGNALS:
    void RcsdkConnectionStatusSignal(rc_connection_status code);

public:
    explicit RtcLiveModel(QWidget *parent = nullptr);
    ~RtcLiveModel();

    static void RcsdkConnectionStatusCB(HANDLE context,
                                        rc_connection_status code);


protected:
    // 回调通知信号槽函数
    void RcsdkConnectionStatusNotify(rc_connection_status code);
    void RoomJoinedNotify(int code);
    void RoomLeftNotify(int code);
    void UserJoinedNotify(QString userId);
    void UserOfflineNotify(QString userId);
    void UserLeftNotify(QString userId);
    void RemotePublishedNotify(QString userId, rcrtc::RCRTCMediaType type);
    void RemoteUnpublishedNotify(QString userId, rcrtc::RCRTCMediaType type);
    void RemoteStateChangedNotify(QString userId,
                                  rcrtc::RCRTCMediaType type,
                                  bool disabled);
    void RemoteLiveMixPublishedNotify(rcrtc::RCRTCMediaType type);
    void RemoteLiveMixUnpublishedNotify(rcrtc::RCRTCMediaType type);
    void RemoteLiveMixSubscribedNotify(rcrtc::RCRTCMediaType type,
                                       int code,
                                       QString errMsg);
    void RemoteLiveMixUnsubscribedNotify(rcrtc::RCRTCMediaType type,
                                         int code,
                                         QString errMsg);
    void RemoteLiveMixFirstFrameNotify(rcrtc::RCRTCMediaType type);
    void RemoteCustomStreamPublishedNotify(QString userId,
                                           QString tag,
                                           rcrtc::RCRTCMediaType type);

    void RemoteCustomStreamUnpublishedNotify(QString userId,
                                             QString tag,
                                             rcrtc::RCRTCMediaType type);
    void RemoteCustomStreamStateChangedNotify(QString userId,
                                              QString tag,
                                              rcrtc::RCRTCMediaType type,
                                              bool disabled);
    void RemoteCustomStreamFirstFrameNotify(QString userId,
                                            QString tag,
                                            rcrtc::RCRTCMediaType type);
    void PublishedNotify(rcrtc::RCRTCMediaType type, int code);
    void UnpublishedNotify(rcrtc::RCRTCMediaType type, int code);
    void SubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code);
    void UnsubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code);
    void CustomStreamSubscribedNotify(QString userId,
                                      QString tag,
                                      rcrtc::RCRTCMediaType type,
                                      int code,
                                      QString errMsg);

    void CustomStreamUnsubscribedNotify(QString userId,
                                        QString tag,
                                        rcrtc::RCRTCMediaType type,
                                        int code,
                                        QString errMsg);
    void LiveRoleSwitchedNotify(rcrtc::RCRTCRole curRole,
                                int code,
                                QString errMsg);

    void RemoteLiveRoleSwitchedNotify(QString roomId,
                                      QString userId,
                                      rcrtc::RCRTCRole role);

    // 界面槽函数
    void CreateEngineBtnClicked();
    void DestroyEngineBtnClicked();
    void EnterRoomBtnClicked();
    void LeaveRoomBtnClicked();
    void PublishedStreamBtnClicked();
    void UnpublisedStreamBtnClicked();
    void SubscribedStreamBtnClicked();
    void UnsubscribedBtnClicked();
    void PublishedShareBtnClicked();
    void UnpublishedShareBtnClicked();
    void SubscribedLiveMixBtnClicked();
    void UnsubscribedLiveMixBtnClicked();
    void SwitchAnchorBtnClicked();
    void SwitchAudienceBtnClicked();
    void SetLiveMixModelBtnClicked();

private:
    void connectSignals();
    void disconnectSignals();
    bool CheckingUserInformation();
    void ModifyBtnStatus();
    bool CreateEngine();
    bool DestroyEngine();
    bool ConnectServer();
    bool DisconnectServer();
    bool EnterRoom();
    bool LeaveRoom();
    bool SetDefaultVideoConfig();
    bool PublishedStream();
    bool UnpublisedStream();
    void SubscribedStream();
    void Unsubscribed();
    bool PublishedShare();
    bool UnpublishedShare();


    void InsterRemoteVideoRender(const RemoteMediaInfo&  media_info,  RemoteStreamType type);
    void RemoveRemoteVideoRender(const RemoteMediaInfo&  media_info);
    void RemoveRemoteVideoRender(const QString& user_id);
    void ClearAllRemoteVIdeoRender();

    void NotifySubscribedStatus(const RemoteMediaInfo&  media_info, bool is_subscribed);
    void InsterRemoteMediaInfo(const RemoteMediaInfo&  media_info);
    void RemoveRemoteMediaInfo(const RemoteMediaInfo&  media_info);
    void RemoveRemoteMediaInfo(const QString& user_id);
    void ClearAllRemoteMediaInfo();
    void AttachLocalViewRender();
    void DetachLocalViewRender();
    void SwitchLiveMixModel1st();
    void SwitchLiveMixModel2nd();
    void SwitchLiveMixModel3rd();
private:
    Ui::RtcLiveModel *ui;
    std::string app_key_ ;
    std::string token_ ;
    std::string navigation_;
    std::string room_id_ ;
    std::string user_name_;

    bool is_engine_;
    bool is_join_room_;
    bool is_anchor_;
    bool is_publishe_;
    bool is_share_;
    HANDLE_IM_ENGINE handle_im_;
    rcrtc::RCRTCEngine* rcrtc_engine_;
    RcRtcListenerImpl* rcrtc_listener_impl_;
    rcrtc::RCRTCEngineSetup* engine_setup_;
    rcrtc::IRCRTCView* view_render_;
    QReadWriteLock mutex_remote_view_;
    QReadWriteLock mutex_remote_media_;
    std::map<RemoteMediaInfo, RtcVideoRender*> map_remote_view_;
    std::list<RemoteMediaInfo> remote_media_list_;
    std::list<RemoteMediaInfo> remote_custom_media_list_;
    std::list<RemoteMediaInfo> remote_live_media_list_;
    int live_mix_model_;
};

#endif // RTC_LIVE_MODEL_H
