#include "rtc_live_model.h"
#include "ui_rtc_live_model.h"

#include "utility.h"
#include "rcrtc_listener_impl.h"
#include "rtc_video_render.h"

#include <QMessageBox>
#include <QDebug>
#include <QDir>

RtcLiveModel::RtcLiveModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtcLiveModel),
    is_engine_(false),
    is_join_room_(false),
    is_publishe_(false),
    is_share_(false),
    rcrtc_engine_(nullptr),
    rcrtc_listener_impl_(nullptr),
    engine_setup_(nullptr),
    view_render_(nullptr),
    live_mix_model_(0)
{
    ui->setupUi(this);

    connect(this, &RtcLiveModel::RcsdkConnectionStatusSignal, this, &RtcLiveModel::RcsdkConnectionStatusNotify);

    connect(ui->btn_create_engine, &QPushButton::clicked, this, &RtcLiveModel::CreateEngineBtnClicked);
    connect(ui->btn_destroy_engine, &QPushButton::clicked, this,  &RtcLiveModel::DestroyEngineBtnClicked);
    connect(ui->btn_enter_room, &QPushButton::clicked, this,  &RtcLiveModel::EnterRoomBtnClicked);
    connect(ui->btn_leave_room, &QPushButton::clicked, this,  &RtcLiveModel::LeaveRoomBtnClicked);
    connect(ui->btn_published_stream, &QPushButton::clicked, this,  &RtcLiveModel::PublishedStreamBtnClicked);
    connect(ui->btn_unpublished_stream, &QPushButton::clicked, this,  &RtcLiveModel::UnpublisedStreamBtnClicked);
    connect(ui->btn_subscribed_stream, &QPushButton::clicked, this,  &RtcLiveModel::SubscribedStreamBtnClicked);
    connect(ui->btn_unsubscribed_stream, &QPushButton::clicked, this,  &RtcLiveModel::UnsubscribedBtnClicked);
    connect(ui->btn_published_share, &QPushButton::clicked, this,  &RtcLiveModel::PublishedShareBtnClicked);
    connect(ui->btn_unpublished_share, &QPushButton::clicked, this,  &RtcLiveModel::UnpublishedShareBtnClicked);
    connect(ui->btn_subscribed_live_mix, &QPushButton::clicked, this,  &RtcLiveModel::SubscribedLiveMixBtnClicked);
    connect(ui->btn_unsubscribed_live_mix, &QPushButton::clicked, this,  &RtcLiveModel::UnsubscribedLiveMixBtnClicked);
    connect(ui->btn_switch_anchor, &QPushButton::clicked, this,  &RtcLiveModel::SwitchAnchorBtnClicked);
    connect(ui->btn_switch_audience, &QPushButton::clicked, this,  &RtcLiveModel::SwitchAudienceBtnClicked);
    connect(ui->btn_set_live_mix_modle, &QPushButton::clicked, this,  &RtcLiveModel::SetLiveMixModelBtnClicked);

    rcrtc_listener_impl_ = new RcRtcListenerImpl();
    ui->radio_anchor->setChecked(true);
    ui->edit_rtc_navigation_url->setText("nav.cn.ronghub.com");
    connectSignals();

    ModifyBtnStatus();
}

RtcLiveModel::~RtcLiveModel()
{
    delete ui;
}


void RtcLiveModel::RcsdkConnectionStatusCB(HANDLE context,
                                              rc_connection_status code) {
    qInfo() << "RcsdkConnectionStatusCB, code :" << code;
    RtcLiveModel* model = (RtcLiveModel*)context;
    if (nullptr != model) {
        Q_EMIT model->RcsdkConnectionStatusSignal(code);
    }
}

void RtcLiveModel::RcsdkConnectionStatusNotify(rc_connection_status code)
{
    qInfo("RcsdkConnectionStatusNotify crc_connection_statusde = %d",
          static_cast<int>(code));
    QString msg ="";
    if (RCIM_CONNECTION_CONNECTED == code) {
        is_engine_ = true;
        ModifyBtnStatus();
    } else if (RCIM_CONNECTION_UNCONNECTED == code) {

    } else if (RCIM_CONNECTION_SIGN_OUT == code) {
        is_engine_ = false;
        ModifyBtnStatus();
        DestroyEngine();
    } else if(RCIM_CONNECTION_KICKED_OFF == code){

    }
}

void RtcLiveModel::RoomJoinedNotify(int code){
    if( 0 == code){
        is_join_room_ = true;
        ModifyBtnStatus();
        QMessageBox::information(NULL, "信息", "成功进入房间", QMessageBox::Yes );
    } else {
        QString msg;
        msg.append("进入房间失败，错误码：");
        msg.append(QString::number(code));
        QMessageBox::critical(NULL, "警告", msg, QMessageBox::Yes );
    }
}
void RtcLiveModel::RoomLeftNotify(int code){
    is_join_room_ = false;
    ModifyBtnStatus();
    live_mix_model_ = 0;
    if(0 == code){
        QMessageBox::information(NULL, "信息", "离开房间成功!", QMessageBox::Yes );
    }
}
void RtcLiveModel::UserJoinedNotify(QString userId){
    RemoveRemoteMediaInfo(userId);
    RemoveRemoteVideoRender(userId);
}
void RtcLiveModel::UserOfflineNotify(QString userId){
    RemoveRemoteMediaInfo(userId);
    RemoveRemoteVideoRender(userId);
}
void RtcLiveModel::UserLeftNotify(QString userId){}
void RtcLiveModel::RemotePublishedNotify(QString userId, rcrtc::RCRTCMediaType type){
    qInfo() << "RemotePublishedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, "", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        InsterRemoteVideoRender(info, STREAM_TYPE_DEFAULT);
    }
    InsterRemoteMediaInfo(info);
}
void RtcLiveModel::RemoteUnpublishedNotify(QString userId, rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteUnpublishedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, "", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        RemoveRemoteVideoRender(info);
    }
    RemoveRemoteMediaInfo(info);
}
void RtcLiveModel::RemoteStateChangedNotify(QString userId,
                                               rcrtc::RCRTCMediaType type,
                                               bool disabled){
    qInfo() << "RemoteStateChangedNotify user id:"<< userId << ", media type:" << static_cast<int>(type) << ", is diabled:" << disabled;
}

void RtcLiveModel::RemoteLiveMixPublishedNotify(rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteLiveMixPublishedNotify, media type:" << static_cast<int>(type);
    RemoteMediaInfo info("live_mix", "live_mix", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        InsterRemoteVideoRender(info, STREAM_TYPE_LIVE);
    }
    InsterRemoteMediaInfo(info);
}

void RtcLiveModel::RemoteLiveMixUnpublishedNotify(rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteLiveMixUnpublishedNotify, media type:" << static_cast<int>(type) ;
    RemoteMediaInfo info("live_mix", "live_mix", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        RemoveRemoteVideoRender(info);
    }
    RemoveRemoteMediaInfo(info);
}

void RtcLiveModel::RemoteLiveMixSubscribedNotify(rcrtc::RCRTCMediaType type,
                                   int code,
                                   QString errMsg){
    qInfo() << "RemoteLiveMixSubscribedNotify, media type:" << static_cast<int>(type) << ", code:" << code << ", errMsg" << errMsg;
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video("live_mix", "live_mix", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, 0==code);
    }
}

void RtcLiveModel::RemoteLiveMixUnsubscribedNotify(rcrtc::RCRTCMediaType type,
                                     int code,
                                     QString errMsg){
    qInfo() << "RemoteLiveMixUnsubscribedNotify, media type:" << static_cast<int>(type) << ", code:" << code << ", errMsg" << errMsg;
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video("live_mix", "live_mix", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, false);
    }
}

void RtcLiveModel::RemoteLiveMixFirstFrameNotify(rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteLiveMixFirstFrameNotify, media type:" << static_cast<int>(type);
}

void RtcLiveModel::RemoteCustomStreamPublishedNotify(QString userId,
                                                        QString tag,
                                                        rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamPublishedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, tag, type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        InsterRemoteVideoRender(info, STREAM_TYPE_CUSTOM);
    }
    InsterRemoteMediaInfo(info);
}

void RtcLiveModel::RemoteCustomStreamUnpublishedNotify(QString userId,
                                                          QString tag,
                                                          rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamUnpublishedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, tag, type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        RemoveRemoteVideoRender(info);
    }
    RemoveRemoteMediaInfo(info);
}
void RtcLiveModel::RemoteCustomStreamStateChangedNotify(QString userId,
                                                           QString tag,
                                                           rcrtc::RCRTCMediaType type,
                                                           bool disabled){
    qInfo() << "RemoteCustomStreamStateChangedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type) << ", is diabled:" << disabled;
}
void RtcLiveModel::RemoteCustomStreamFirstFrameNotify(QString userId,
                                                         QString tag,
                                                         rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamFirstFrameNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
}

void RtcLiveModel::PublishedNotify(rcrtc::RCRTCMediaType type, int code){
    qInfo() << "PublishedNotify, media type:" << static_cast<int>(type);
    if(0 != code){
        QString msg = "发布默认资源失败！错误码：" + QString::number(code);
         QMessageBox::critical(NULL, "警告", msg, QMessageBox::Yes );
    } else {
        QMessageBox::information(NULL, "信息", "发布默认资源成功！", QMessageBox::Yes );
    }
}
void RtcLiveModel::UnpublishedNotify(rcrtc::RCRTCMediaType type, int code){
    qInfo() << "UnpublishedNotify , media type:" << static_cast<int>(type);
    if(0 != code){
        QString msg = "取消发布默认资源失败！错误码：" + QString::number(code);
         QMessageBox::critical(NULL, "警告", msg, QMessageBox::Yes );
    } else {
        QMessageBox::information(NULL, "信息", "取消发布默认资源成功！", QMessageBox::Yes );
    }
}
void RtcLiveModel::SubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code){
    qInfo() << "SubscribedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, "", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, 0==code);
    }
}
void RtcLiveModel::UnsubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code){
    qInfo() << "UnsubscribedNotify user id:"<< userId <<", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, "", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, false);
    }
}
void RtcLiveModel::CustomStreamSubscribedNotify(QString userId,
                                                   QString tag,
                                                   rcrtc::RCRTCMediaType type,
                                                   int code,
                                                   QString errMsg){
    qInfo() << "UnsubscribedNotify user id:"<< userId <<", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, tag, rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, false);
    }
}

void RtcLiveModel::CustomStreamUnsubscribedNotify(QString userId,
                                                     QString tag,
                                                     rcrtc::RCRTCMediaType type,
                                                     int code,
                                                     QString errMsg){
    qInfo() << "UnsubscribedNotify user id:"<< userId <<", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, tag, rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, false);
    }
}

void RtcLiveModel::LiveRoleSwitchedNotify(rcrtc::RCRTCRole curRole,
                                              int code,
                                              QString errMsg) {
  if (code != 0) {
    return;
  }

    if (curRole == rcrtc::RCRTCRole::LIVE_BROADCASTER) {
        is_anchor_ = true;
    } else {
        is_anchor_ = false;
    }
    ClearAllRemoteMediaInfo();
    ClearAllRemoteVIdeoRender();
    ModifyBtnStatus();
}

void RtcLiveModel::RemoteLiveRoleSwitchedNotify(QString roomId,
                                                    QString userId,
                                                    rcrtc::RCRTCRole role) {
    RemoveRemoteVideoRender(userId);
    RemoveRemoteMediaInfo(userId);
}

void RtcLiveModel::CreateEngineBtnClicked(){
    if(false == CheckingUserInformation()){
        return;
    }
    if(CreateEngine()){
        if(false == ConnectServer()){
            QMessageBox::critical(NULL, "警告", "连接服务失败！", QMessageBox::Yes );
        }

    } else {
        QMessageBox::critical(NULL, "警告", "引擎创建失败！", QMessageBox::Yes );
    }

}
void RtcLiveModel::DestroyEngineBtnClicked(){
    if(is_join_room_){
        QMessageBox::critical(NULL, "警告", "请先退出房间，在销毁RTC引擎！", QMessageBox::Yes );
        return;
    }
    if(false == DisconnectServer()){
        DestroyEngine();
    }
}
void RtcLiveModel::EnterRoomBtnClicked(){
    if(false == EnterRoom()){
        QMessageBox::critical(NULL, "警告", "进入房间失败！", QMessageBox::Yes );
    }
}
void RtcLiveModel::LeaveRoomBtnClicked(){
    if(false == LeaveRoom()){
        QMessageBox::critical(NULL, "警告", "离开房间失败！", QMessageBox::Yes );
    }
    ClearAllRemoteMediaInfo();
    ClearAllRemoteVIdeoRender();
    DetachLocalViewRender();
}
void RtcLiveModel::PublishedStreamBtnClicked(){
    if(false == PublishedStream()){
        QMessageBox::critical(NULL, "警告", "发布默认音视频资源失败！", QMessageBox::Yes );
    } else {
        AttachLocalViewRender();
        is_publishe_ = true;
    }
}
void RtcLiveModel::UnpublisedStreamBtnClicked(){
    if(false == UnpublisedStream()){
        QMessageBox::critical(NULL, "警告", "取消发布默认音视频资源失败！", QMessageBox::Yes );
    } else {
        DetachLocalViewRender();
        is_publishe_ = false;
    }
}
void RtcLiveModel::SubscribedStreamBtnClicked(){
    SubscribedStream();
}
void RtcLiveModel::UnsubscribedBtnClicked(){
    Unsubscribed();
}
void RtcLiveModel::PublishedShareBtnClicked(){
    SetDefaultVideoConfig();
    if(false == PublishedShare()){
        QMessageBox::critical(NULL, "警告", "屏幕共享失败！", QMessageBox::Yes );
    } else {
        is_share_ = true;
    }
}
void RtcLiveModel::UnpublishedShareBtnClicked(){
    UnpublishedShare();
    is_share_ = false;
}

void RtcLiveModel::SubscribedLiveMixBtnClicked(){
    QReadLocker locker(&mutex_remote_media_);
    if(remote_live_media_list_.empty()){
        QMessageBox::critical(NULL, "警告", "没有直播合流可以订阅！", QMessageBox::Yes );
        return;
    }
    if(nullptr == rcrtc_engine_){
        return;
    }
    bool is_audio =false;
    bool is_video = false;
    for(auto& it : remote_live_media_list_){
        if(rcrtc::RCRTCMediaType::AUDIO == it.media_type_ || rcrtc::RCRTCMediaType::AUDIO_VIDEO == it.media_type_){
            is_audio = true;
        }
        if(rcrtc::RCRTCMediaType::VIDEO == it.media_type_ || rcrtc::RCRTCMediaType::AUDIO_VIDEO == it.media_type_){
            is_video = true;
        }
    }
    int32_t ret = -1;
    if(is_video && is_audio){
        ret = rcrtc_engine_->subscribeLiveMix(rcrtc::RCRTCMediaType::AUDIO_VIDEO, false);
    } else if(is_video){
        ret = rcrtc_engine_->subscribeLiveMix(rcrtc::RCRTCMediaType::VIDEO, false);
    }else if(is_audio){
        ret = rcrtc_engine_->subscribeLiveMix(rcrtc::RCRTCMediaType::AUDIO, false);
    }
}
void RtcLiveModel::UnsubscribedLiveMixBtnClicked(){
    if(remote_live_media_list_.empty()){
        QMessageBox::critical(NULL, "警告", "没有直播合流可以取消订阅！", QMessageBox::Yes );
        return;
    }
    if(nullptr == rcrtc_engine_){
        return;
    }
    bool is_audio =false;
    bool is_video = false;
    for(auto& it : remote_live_media_list_){
        if(rcrtc::RCRTCMediaType::AUDIO == it.media_type_ || rcrtc::RCRTCMediaType::AUDIO_VIDEO == it.media_type_){
            is_audio = true;
        }
        if(rcrtc::RCRTCMediaType::VIDEO == it.media_type_ || rcrtc::RCRTCMediaType::AUDIO_VIDEO == it.media_type_){
            is_video = true;
        }
    }
    int32_t ret = -1;
    if(is_video && is_audio){
        ret = rcrtc_engine_->unsubscribeLiveMix(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
    } else if(is_video){
        ret = rcrtc_engine_->unsubscribeLiveMix(rcrtc::RCRTCMediaType::VIDEO);
    }else if(is_audio){
        ret = rcrtc_engine_->unsubscribeLiveMix(rcrtc::RCRTCMediaType::AUDIO);
    }
}
void RtcLiveModel::SwitchAnchorBtnClicked(){
    if(is_anchor_){
        QMessageBox::critical(NULL, "警告", "当前角色为主播！", QMessageBox::Yes );
        return;
    }
    int32_t ret = rcrtc_engine_->switchLiveRole(rcrtc::RCRTCRole::LIVE_BROADCASTER);
    if(0 != ret){
         QMessageBox::critical(NULL, "警告", "角色切换失败！", QMessageBox::Yes );
    }
}
void RtcLiveModel::SwitchAudienceBtnClicked(){
    if(!is_anchor_){
        QMessageBox::critical(NULL, "警告", "当前角色为观众！", QMessageBox::Yes );
        return;
    }
    if(nullptr == rcrtc_engine_){
        return;
    }
   int32_t ret = rcrtc_engine_->switchLiveRole(rcrtc::RCRTCRole::LIVE_AUDIENCE);
   if(0 != ret){
        QMessageBox::critical(NULL, "警告", "角色切换失败！", QMessageBox::Yes );
   }
}
void RtcLiveModel::SetLiveMixModelBtnClicked(){
    if(0 == live_mix_model_ % 3){
        SwitchLiveMixModel1st();
    } else if(1 == live_mix_model_ % 3){
        SwitchLiveMixModel2nd();
    } if(2 == live_mix_model_ % 3){
        SwitchLiveMixModel3rd();
    }
    live_mix_model_++;
}

void RtcLiveModel::connectSignals(){
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RoomJoinedSignal, this, &RtcLiveModel::RoomJoinedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RoomLeftSignal, this, &RtcLiveModel::RoomLeftNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserJoinedSignal, this, &RtcLiveModel::UserJoinedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserOfflineSignal, this, &RtcLiveModel::UserOfflineNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserLeftSignal, this, &RtcLiveModel::UserLeftNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemotePublishedSignal, this, &RtcLiveModel::RemotePublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteUnpublishedSignal, this, &RtcLiveModel::RemoteUnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteStateChangedSignal, this, &RtcLiveModel::RemoteStateChangedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteLiveMixFirstFrameSignal, this,&RtcLiveModel::RemoteLiveMixFirstFrameNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteLiveMixPublishedSignal, this, &RtcLiveModel::RemoteLiveMixPublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteLiveMixUnpublishedSignal, this, &RtcLiveModel::RemoteLiveMixUnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::LiveMixSubscribedSignal, this, &RtcLiveModel::RemoteLiveMixSubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::LiveMixUnsubscribedSignal, this, &RtcLiveModel::RemoteLiveMixUnsubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::PublishedSignal, this, &RtcLiveModel::PublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UnpublishedSignal, this, &RtcLiveModel::UnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::SubscribedSignal, this, &RtcLiveModel::SubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UnsubscribedSignal, this, &RtcLiveModel::UnsubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamPublishedSignal, this, &RtcLiveModel::RemoteCustomStreamPublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamUnpublishedSignal, this, &RtcLiveModel::RemoteCustomStreamUnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamStateChangedSignal, this, &RtcLiveModel::RemoteCustomStreamStateChangedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamFirstFrameSignal, this, &RtcLiveModel::RemoteCustomStreamFirstFrameNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::CustomStreamSubscribedSignal, this,  &RtcLiveModel::CustomStreamSubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::CustomStreamUnsubscribedSignal, this, &RtcLiveModel::CustomStreamUnsubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::LiveRoleSwitchedSignal, this, &RtcLiveModel::LiveRoleSwitchedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteLiveRoleSwitchedSignal, this,  &RtcLiveModel::RemoteLiveRoleSwitchedNotify);
}
void RtcLiveModel::disconnectSignals(){}
bool RtcLiveModel::CheckingUserInformation()
{
    app_key_ = ConvertTostdString(ui->edit_rtc_appkey->text());
    token_ = ConvertTostdString(ui->edit_rtc_token->text());
    navigation_ = ConvertTostdString(ui->edit_rtc_navigation_url->text());
    room_id_ = ConvertTostdString(ui->edit_rtc_room_id->text());
    user_name_ = ConvertTostdString(ui->edit_rtc_UserName->text());
    if(app_key_.empty() || token_.empty() || navigation_.empty() || room_id_.empty() || user_name_.empty()){
        QMessageBox::critical(NULL, "警告", "用户信息不完整", QMessageBox::Yes );
        return false;
    }
    return true;
}

void RtcLiveModel::ModifyBtnStatus()
{
    ui->btn_create_engine->setEnabled(!is_engine_);
    ui->btn_destroy_engine->setEnabled(is_engine_);
    ui->btn_enter_room->setEnabled(is_engine_  && !is_join_room_);
    ui->btn_leave_room->setEnabled(is_engine_  && is_join_room_);
    ui->btn_published_stream->setEnabled(is_engine_  && is_join_room_&& is_anchor_);
    ui->btn_unpublished_stream->setEnabled(is_engine_  && is_join_room_&& is_anchor_);
    ui->btn_subscribed_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_unsubscribed_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_published_share->setEnabled(is_engine_  && is_join_room_&& is_anchor_);
    ui->btn_unpublished_share->setEnabled(is_engine_  && is_join_room_&& is_anchor_);

    ui->radio_anchor->setEnabled(is_engine_ && !is_join_room_);
    ui->radio_audience->setEnabled(is_engine_ && !is_join_room_);
    ui->btn_switch_anchor->setEnabled(is_engine_ && is_join_room_);
    ui->btn_switch_audience->setEnabled(is_engine_ && is_join_room_);
    ui->btn_set_live_mix_modle->setEnabled(is_engine_ && is_join_room_ && is_anchor_);
    ui->btn_subscribed_live_mix->setEnabled(is_engine_ && is_join_room_ && !is_anchor_);
    ui->btn_unsubscribed_live_mix->setEnabled(is_engine_ && is_join_room_ && !is_anchor_);

    QString role = is_anchor_?"主播":"观众";
    ui->label_curl_role->setText(role);
}

bool RtcLiveModel::CreateEngine(){
    int error_code = -1;
    handle_im_ = rcim_init(app_key_.c_str(), navigation_.c_str(), "./", &error_code);
    if(nullptr == handle_im_){
        return false;
    }
    QDir dir;
    QString dir_path = QCoreApplication::applicationDirPath() + "/log";
    if (!dir.exists(dir_path)) {
        dir.mkdir(dir_path);  //创造一个文件夹，以目前的年月日来命名的
    }
    engine_setup_ = rcrtc::RCRTCEngineSetup::create();
    if (engine_setup_) {
        engine_setup_->setReconnectable(true);
        auto log = engine_setup_->CreateLogSetup();
        if (log) {
            log->setLogFolder(ConvertTostdString(dir_path));
            log->setLogLevel(1);
        }
        rcrtc_engine_ = rcrtc::RCRTCEngine::create(handle_im_, engine_setup_);
        if (nullptr == rcrtc_engine_) {
            qDebug("RTCEngine init failed.\n");
            return false;
        }
        rcrtc_engine_->setListener(rcrtc_listener_impl_);
        return true;
    }
    return false;
}

bool RtcLiveModel::DestroyEngine(){
    if (nullptr != rcrtc_engine_) {
        qInfo() << "DestroyRtcEngine";
        rcrtc_engine_->setListener(nullptr);
        rcrtc_engine_->setStatsListener(nullptr);
        rcrtc_engine_->destroy();
        rcrtc_engine_ = nullptr;
    }
    if(nullptr != engine_setup_){
        rcrtc::RCRTCEngineSetup::destroy(&engine_setup_);
    }
    if (nullptr != handle_im_) {
        qInfo() << "UnInitRcIm";
        rcim_uninit(handle_im_);
        handle_im_ = nullptr;
    }
    return true;
}
bool RtcLiveModel::ConnectServer(){
    if(0 == rcim_set_connection_callback(handle_im_, RcsdkConnectionStatusCB, this)){
        if(0 == rcim_connect(handle_im_, token_.c_str())){
            return true;
        }
    }
    return false;
}
bool RtcLiveModel::DisconnectServer(){
    if(0 == rcim_disconnect(handle_im_)){
        return true;
    }
    return false;
}

bool RtcLiveModel::EnterRoom(){
    int32_t ret =-1;
    rcrtc::RCRTCRoomSetup* setup = rcrtc::RCRTCRoomSetup::create();
    if(nullptr == setup){
        return false;
    } else {
        is_anchor_ = ui->radio_anchor->isChecked();
        auto role = is_anchor_ ? rcrtc::RCRTCRole::LIVE_BROADCASTER : rcrtc::RCRTCRole::LIVE_AUDIENCE;
        setup->setRole(role);
        setup->setJoinType(rcrtc::RCRTCJoinType::KICK_OTHER_DEVICE);
        setup->setMediaType(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
        ret = rcrtc_engine_->joinRoom(room_id_,setup);
        rcrtc::RCRTCRoomSetup::destroy(&setup);
    }
    return ret == 0;
}
bool RtcLiveModel::LeaveRoom(){
    int32_t ret = rcrtc_engine_->leaveRoom();
    return ret == 0;
}

bool RtcLiveModel::SetDefaultVideoConfig()
{
    if(nullptr == rcrtc_engine_){
        return false;
    }

    rcrtc::RCRTCVideoConfig *config = rcrtc::RCRTCVideoConfig::create();
    config->setFps(rcrtc::RCRTCVideoFps::FPS_15);
    config->setResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_480_640);
    int32_t minBitrate, maxBitrate;
    config->getMaxAndMinBitrate(&minBitrate, &maxBitrate);
    config->setMinBitrate(minBitrate);
    config->setMaxBitrate(maxBitrate);
    config->setMirror(false);
    int err_code = rcrtc_engine_->setVideoConfig(config);
    rcrtc::RCRTCVideoConfig::destroy(&config);
    if(err_code !=0) {
        qCritical() << "set video config failed.";
    }
    return 0 == err_code;
}

bool RtcLiveModel::PublishedStream(){
    if(nullptr == rcrtc_engine_){
        return false;
    }
    int32_t ret = rcrtc_engine_->publish(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
    return 0 == ret;
}
bool RtcLiveModel::UnpublisedStream()
{
    if(nullptr == rcrtc_engine_){
        return false;
    }
    int32_t ret = rcrtc_engine_->unpublish(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
    return 0 == ret;
}


void RtcLiveModel::SubscribedStream(){
    QReadLocker locker(&mutex_remote_media_);
    if(nullptr == rcrtc_engine_){
        return ;
    }
    std::list<std::string> default_list;
    for(auto& it :remote_media_list_){
        default_list.emplace_back(ConvertTostdString(it.user_id_));
    }
    rcrtc_engine_->subscribe(default_list, rcrtc::RCRTCMediaType::AUDIO_VIDEO);

    for(auto& it : remote_custom_media_list_){
        rcrtc_engine_->subscribeCustomStream(ConvertTostdString(it.user_id_),ConvertTostdString(it.stream_tag_), it.media_type_);
    }
}
void RtcLiveModel::Unsubscribed(){
    QReadLocker locker(&mutex_remote_media_);
    if(nullptr == rcrtc_engine_){
        return ;
    }
    std::list<std::string> default_list;
    for(auto& it :remote_media_list_){
        default_list.emplace_back(ConvertTostdString(it.user_id_));
    }
    rcrtc_engine_->unsubscribe(default_list, rcrtc::RCRTCMediaType::AUDIO_VIDEO);

    for(auto& it : remote_custom_media_list_){
        rcrtc_engine_->unsubscribeCustomStream(ConvertTostdString(it.user_id_),ConvertTostdString(it.stream_tag_), it.media_type_);
    }
}

bool RtcLiveModel::PublishedShare(){
    if(nullptr == rcrtc_engine_){
        return false;
    }
    std::string stream_tag =  "RtcScreenSharing";
    std::list<rcrtc::RCRTCDesktopSource*> monitor;
    int32_t ret = rcrtc_engine_->getMonitorList(monitor);
    if(0 != ret|| monitor.empty()){
        return false;
    }
    ret = rcrtc_engine_->createCustomStreamByMonitor(monitor.front(), stream_tag);
    if(0 != ret){
        return false;
    }
    rcrtc::RCRTCVideoConfig* video_config = rcrtc::RCRTCVideoConfig::create();
    int maxBit;
    int minBit;
    video_config->setResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_1080_1920);
    video_config->setFps(rcrtc::RCRTCVideoFps::FPS_15);
    video_config->getMaxAndMinBitrate(&maxBit, &minBit);
    video_config->setMaxBitrate(2000);
    video_config->setMinBitrate(minBit);
    rcrtc_engine_->setCustomStreamVideoConfig(stream_tag, video_config);

    ret = rcrtc_engine_->publishCustomStream(stream_tag, rcrtc::RCRTCMediaType::VIDEO);
    rcrtc::RCRTCVideoConfig::destroy(&video_config);
    return true;
}

bool RtcLiveModel::UnpublishedShare(){
    if(nullptr == rcrtc_engine_){
        return false;
    }
    std::string stream_tag =  "RtcScreenSharing";
    std::list<std::string> list;
    list.push_back(stream_tag);
    rcrtc_engine_->unpublishCustomStream(stream_tag, rcrtc::RCRTCMediaType::VIDEO);
    rcrtc_engine_->destroyCustomStream(list);
    return true;
}

void RtcLiveModel::InsterRemoteVideoRender(const RemoteMediaInfo&  media_info,  RemoteStreamType type){
    QWriteLocker locker(&mutex_remote_view_);
    auto Iter = map_remote_view_.find(media_info);
    if (Iter == map_remote_view_.end()) {
        RtcVideoRender* video_render = new RtcVideoRender();
        if(video_render){
            video_render->SetStreamInfo(rcrtc_engine_, media_info.user_id_, media_info.stream_tag_, type);
            video_render->AttachViewRender();
            ui->remotre_view_layout->addWidget(video_render);
        }
        map_remote_view_[media_info] = video_render;
    }
}
void RtcLiveModel::RemoveRemoteVideoRender(const RemoteMediaInfo&  media_info){
    QWriteLocker locker(&mutex_remote_view_);
    auto Iter = map_remote_view_.find(media_info);
    if (Iter != map_remote_view_.end()) {
        RtcVideoRender* video_render = Iter->second;
        if(video_render){
            video_render->DetachViewRender();
            ui->remotre_view_layout->removeWidget(video_render);
            delete  video_render;
            video_render = nullptr;
        }
        map_remote_view_.erase(Iter);
    }
}

void RtcLiveModel::RemoveRemoteVideoRender(const QString &user_id)
{
    QWriteLocker locker(&mutex_remote_view_);
    auto it = map_remote_view_.begin();
    while(it != map_remote_view_.end()){
        if(it->first.user_id_ == user_id){
            RtcVideoRender* video_render = it->second;
            if(video_render){
                video_render->DetachViewRender();
                ui->remotre_view_layout->removeWidget(video_render);
                delete  video_render;
                video_render = nullptr;
            }
            it = map_remote_view_.erase(it);
        } else {
            it++;
        }
    }
}
void RtcLiveModel::ClearAllRemoteVIdeoRender()
{
    QWriteLocker locker(&mutex_remote_view_);
    auto it = map_remote_view_.begin();
    while(it != map_remote_view_.end()){
        RtcVideoRender* video_render = it->second;
        if(video_render){
            video_render->DetachViewRender();
            ui->remotre_view_layout->removeWidget(video_render);
            delete  video_render;
            video_render = nullptr;
        }
        it = map_remote_view_.erase(it);
    }
}

void RtcLiveModel::NotifySubscribedStatus(const RemoteMediaInfo &media_info, bool is_subscribed)
{
    QReadLocker locker(&mutex_remote_view_);
    auto Iter = map_remote_view_.find(media_info);
    if (Iter != map_remote_view_.end()) {
        RtcVideoRender* video_render = Iter->second;
        if(video_render){
            video_render->NotifySubscribedStatus(is_subscribed);
        }
    }
}

void RtcLiveModel::InsterRemoteMediaInfo(const RemoteMediaInfo&  media_info){
    QWriteLocker locker(&mutex_remote_media_);
    if(media_info.stream_tag_ == ""){
        remote_media_list_.push_back(media_info);
    } else if(media_info.stream_tag_ == "live_mix"){
        remote_live_media_list_.push_back(media_info);
    } else {
        remote_custom_media_list_.push_back(media_info);
    }
}
void RtcLiveModel::RemoveRemoteMediaInfo(const RemoteMediaInfo&  media_info){
    QWriteLocker locker(&mutex_remote_media_);
    if(media_info.stream_tag_ == ""){
        auto it = remote_media_list_.begin();
        while(it != remote_media_list_.end()){
            if(*it == media_info){
                it = remote_media_list_.erase(it);
            } else {
                it++;
            }
        }
    } else  if(media_info.stream_tag_ == "live_mix"){
        auto it = remote_live_media_list_.begin();
        while(it != remote_live_media_list_.end()){
            if(*it == media_info){
                it = remote_live_media_list_.erase(it);
            } else {
                it++;
            }
        }
    } else {
        auto it = remote_custom_media_list_.begin();
        while(it != remote_custom_media_list_.end()){
            if(*it == media_info){
                it = remote_custom_media_list_.erase(it);
            } else {
                it++;
            }
        }
    }
}

void RtcLiveModel::RemoveRemoteMediaInfo(const QString &user_id)
{
    QWriteLocker locker(&mutex_remote_media_);
    auto it = remote_media_list_.begin();
    while(it != remote_media_list_.end()){
        if(it->user_id_ == user_id){
            it = remote_media_list_.erase(it);
        } else {
            it++;
        }
    }
    it = remote_custom_media_list_.begin();
    while(it != remote_custom_media_list_.end()){
        if(it->user_id_ == user_id){
            it = remote_custom_media_list_.erase(it);
        } else {
            it++;
        }
    }
    if("live_mix" == user_id){
        remote_live_media_list_.clear();
    }
}
void RtcLiveModel::ClearAllRemoteMediaInfo()
{
    QWriteLocker locker(&mutex_remote_media_);
    remote_media_list_.clear();
    remote_custom_media_list_.clear();
    remote_live_media_list_.clear();
}

void RtcLiveModel::AttachLocalViewRender(){
    if(nullptr == rcrtc_engine_){
        return;
    }
    HANDLE viewId = (HANDLE)ui->widget_local_view->winId();
    view_render_ = rcrtc::IRCRTCView::create((HANDLE)viewId);
    view_render_->setMirror(false);
    view_render_->setFitType(rcrtc::RCRTCViewFitType::FIT);
    rcrtc_engine_->setLocalView(view_render_);
}
void RtcLiveModel::DetachLocalViewRender(){
    if(nullptr == rcrtc_engine_ || nullptr ==view_render_){
        return;
    }
    rcrtc_engine_->removeLocalView();
    rcrtc::IRCRTCView::destroy(&view_render_);
    QString  style = "QWidget{background-color:black;};";
    ui->widget_local_view->setStyleSheet(style);
}

void RtcLiveModel::SwitchLiveMixModel1st(){
    if(nullptr == rcrtc_engine_){
        return;
    }
    rcrtc_engine_->setLiveMixLayoutMode(rcrtc::RCRTCLiveMixLayoutMode::SUSPENSION);
    rcrtc_engine_->setLiveMixRenderMode(rcrtc::RCRTCLiveMixRenderMode::CROP);
    rcrtc_engine_->setLiveMixAudioBitrate(2000 * 1000);
    rcrtc_engine_->setLiveMixVideoBitrate(2000 * 1000, false);
    rcrtc_engine_->setLiveMixVideoBitrate(500 * 1000, true);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_480_640, false);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_360_480, true);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_30, false);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_10, true);
    rcrtc_engine_->setLiveMixBackgroundColor(255,0,0);
}
void RtcLiveModel::SwitchLiveMixModel2nd(){
    if(nullptr == rcrtc_engine_){
        return;
    }
    rcrtc_engine_->setLiveMixLayoutMode(rcrtc::RCRTCLiveMixLayoutMode::ADAPTIVE);
    rcrtc_engine_->setLiveMixRenderMode(rcrtc::RCRTCLiveMixRenderMode::WHOLE);
    rcrtc_engine_->setLiveMixAudioBitrate(2000 * 1000);
    rcrtc_engine_->setLiveMixVideoBitrate(2000 * 1000, false);
    rcrtc_engine_->setLiveMixVideoBitrate(500 * 1000, true);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_1080_1920, false);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_360_480, true);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_15, false);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_8, true);
    rcrtc_engine_->setLiveMixBackgroundColor(0,255,0);
}
void RtcLiveModel::SwitchLiveMixModel3rd(){
    if(nullptr == rcrtc_engine_){
        return;
    }
    std::list<std::string> userIds;
    rcrtc_engine_->setLiveMixLayoutMode(rcrtc::RCRTCLiveMixLayoutMode::CUSTOM);
    rcrtc_engine_->setLiveMixRenderMode(rcrtc::RCRTCLiveMixRenderMode::WHOLE);
    rcrtc_engine_->setLiveMixAudioBitrate(2000 * 1000);
    rcrtc_engine_->setLiveMixVideoBitrate(2000 * 1000, false);
    rcrtc_engine_->setLiveMixVideoBitrate(500 * 1000, true);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_1080_1920, false);
    rcrtc_engine_->setLiveMixVideoResolution(rcrtc::RCRTCVideoResolution::RESOLUTION_360_480, true);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_24, false);
    rcrtc_engine_->setLiveMixVideoFps(rcrtc::RCRTCVideoFps::FPS_8, true);
    rcrtc_engine_->setLiveMixBackgroundColor(0,0,255);
    rcrtc_engine_->setLiveMixCustomAudios(userIds, true);
    {
        QReadLocker locker(&mutex_remote_media_);
        int row = 0;
        int col = 0;
        std::list<rcrtc::RCRTCCustomLayout> layouts;
        if(is_publishe_){
            rcrtc::RCRTCCustomLayout layout;
            layout.userId ="";
            layout.tag = "";
            layout.x = row * 640;
            layout.y = col* 480;
            layout.height = 480;
            layout.width = 640;
            layouts.push_back(layout);
            row++;
            if(row ==2){
                col++;
                row =0;
            }
        }
        if(is_share_){
            rcrtc::RCRTCCustomLayout layout;
            layout.userId ="";
            layout.tag = "RtcScreenSharing";
            layout.x = row * 640;
            layout.y = col* 480;
            layout.height = 480;
            layout.width = 640;
            layouts.push_back(layout);
            row++;
            if(row ==2){
                col++;
                row =0;
            }
        }
        for(auto& it:remote_media_list_){
            if(it.media_type_ == rcrtc::RCRTCMediaType::AUDIO){
                continue;
            }
            if(col > 3){
                break;
            }
            rcrtc::RCRTCCustomLayout layout;
            layout.userId = ConvertTostdString(it.user_id_);
            layout.tag = ConvertTostdString(it.stream_tag_);
            layout.x = row * 640;
            layout.y = col* 480;
            layout.height = 480;
            layout.width = 640;
            layouts.push_back(layout);
            row++;
            if(row ==2){
                col++;
                row =0;
            }
        }
        for(auto& it:remote_custom_media_list_){
            if(it.media_type_ == rcrtc::RCRTCMediaType::AUDIO){
                continue;
            }

            if(col > 3){
                break;
            }
            rcrtc::RCRTCCustomLayout layout;
            layout.userId = ConvertTostdString(it.user_id_);
            layout.tag = ConvertTostdString(it.stream_tag_);
            layout.x = row * 640;
            layout.y = col* 480;
            layout.height = 480;
            layout.width = 640;
            layouts.push_back(layout);
            row++;
            if(row ==2){
                col++;
                row =0;
            }
        }

        if(false == layouts.empty()){
            rcrtc_engine_->setLiveMixCustomLayouts(layouts);
        }
    }
}
