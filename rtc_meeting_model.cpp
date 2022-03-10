#include "rtc_meeting_model.h"
#include "ui_rtc_meeting_model.h"

#include "utility.h"
#include "rcrtc_listener_impl.h"
#include "rtc_video_render.h"

#include <QMessageBox>
#include <QDebug>
#include <QDir>

RtcMeetingModel::RtcMeetingModel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtcMeetingModel),
    is_engine_(false),
    is_join_room_(false),
    rcrtc_engine_(nullptr),
    rcrtc_listener_impl_(nullptr),
    engine_setup_(nullptr),
    view_render_(nullptr)
{
    ui->setupUi(this);

    connect(this, &RtcMeetingModel::RcsdkConnectionStatusSignal, this, &RtcMeetingModel::RcsdkConnectionStatusNotify);

    connect(ui->btn_create_engine, &QPushButton::clicked, this, &RtcMeetingModel::CreateEngineBtnClicked);
    connect(ui->btn_destroy_engine, &QPushButton::clicked, this,  &RtcMeetingModel::DestroyEngineBtnClicked);
    connect(ui->btn_enter_room, &QPushButton::clicked, this,  &RtcMeetingModel::EnterRoomBtnClicked);
    connect(ui->btn_leave_room, &QPushButton::clicked, this,  &RtcMeetingModel::LeaveRoomBtnClicked);
    connect(ui->btn_published_stream, &QPushButton::clicked, this,  &RtcMeetingModel::PublishedStreamBtnClicked);
    connect(ui->btn_unpublished_stream, &QPushButton::clicked, this,  &RtcMeetingModel::UnpublisedStreamBtnClicked);
    connect(ui->btn_subscribed_stream, &QPushButton::clicked, this,  &RtcMeetingModel::SubscribedStreamBtnClicked);
    connect(ui->btn_unsubscribed_stream, &QPushButton::clicked, this,  &RtcMeetingModel::UnsubscribedBtnClicked);
    connect(ui->btn_published_share, &QPushButton::clicked, this,  &RtcMeetingModel::PublishedShareBtnClicked);
    connect(ui->btn_unpublished_share, &QPushButton::clicked, this,  &RtcMeetingModel::UnpublishedShareBtnClicked);

    rcrtc_listener_impl_ = new RcRtcListenerImpl();
    ui->edit_rtc_navigation_url->setText("nav.cn.ronghub.com");
    connectSignals();

    ModifyBtnStatus();
}

RtcMeetingModel::~RtcMeetingModel()
{
    delete ui;
}

void RtcMeetingModel::RcsdkConnectionStatusCB(HANDLE context,
                                              rc_connection_status code) {
    qInfo() << "RcsdkConnectionStatusCB, code :" << code;
    RtcMeetingModel* model = (RtcMeetingModel*)context;
    if (nullptr != model) {
        Q_EMIT model->RcsdkConnectionStatusSignal(code);
    }
}

void RtcMeetingModel::RcsdkConnectionStatusNotify(rc_connection_status code)
{
    qInfo("RcsdkConnectionStatusNotify crc_connection_statusde = %d",
          static_cast<int32_t>(code));
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

void RtcMeetingModel::RoomJoinedNotify(int code){
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
void RtcMeetingModel::RoomLeftNotify(int code){
    is_join_room_ = false;
    ModifyBtnStatus();
    if(0 == code){
        QMessageBox::information(NULL, "信息", "离开房间成功!", QMessageBox::Yes );
    }
}

void RtcMeetingModel::UserJoinedNotify(QString userId){
    RemoveRemoteMediaInfo(userId);
    RemoveRemoteVideoRender(userId);
}
void RtcMeetingModel::UserOfflineNotify(QString userId){
    RemoveRemoteMediaInfo(userId);
    RemoveRemoteVideoRender(userId);
}
void RtcMeetingModel::UserLeftNotify(QString userId){}
void RtcMeetingModel::RemotePublishedNotify(QString userId, rcrtc::RCRTCMediaType type){
    qInfo() << "RemotePublishedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, "", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        InsterRemoteVideoRender(info, STREAM_TYPE_DEFAULT);
    }
    InsterRemoteMediaInfo(info);
}
void RtcMeetingModel::RemoteUnpublishedNotify(QString userId, rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteUnpublishedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, "", type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        RemoveRemoteVideoRender(info);
    }
    RemoveRemoteMediaInfo(info);
}
void RtcMeetingModel::RemoteStateChangedNotify(QString userId,
                                               rcrtc::RCRTCMediaType type,
                                               bool disabled){
    qInfo() << "RemoteStateChangedNotify user id:"<< userId << ", media type:" << static_cast<int>(type) << ", is diabled:" << disabled;
}

void RtcMeetingModel::RemoteCustomStreamPublishedNotify(QString userId,
                                                        QString tag,
                                                        rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamPublishedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, tag, type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        InsterRemoteVideoRender(info, STREAM_TYPE_CUSTOM);
    }
    InsterRemoteMediaInfo(info);
}

void RtcMeetingModel::RemoteCustomStreamUnpublishedNotify(QString userId,
                                                          QString tag,
                                                          rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamUnpublishedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
    RemoteMediaInfo info(userId, tag, type);
    if(rcrtc::RCRTCMediaType::VIDEO == type){
        RemoveRemoteVideoRender(info);
    }
    RemoveRemoteMediaInfo(info);
}
void RtcMeetingModel::RemoteCustomStreamStateChangedNotify(QString userId,
                                                           QString tag,
                                                           rcrtc::RCRTCMediaType type,
                                                           bool disabled){
    qInfo() << "RemoteCustomStreamStateChangedNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type) << ", is diabled:" << disabled;
}
void RtcMeetingModel::RemoteCustomStreamFirstFrameNotify(QString userId,
                                                         QString tag,
                                                         rcrtc::RCRTCMediaType type){
    qInfo() << "RemoteCustomStreamFirstFrameNotify user id:"<< userId << ", tag:" << tag <<", media type:" << static_cast<int>(type);
}

void RtcMeetingModel::PublishedNotify(rcrtc::RCRTCMediaType type, int code){
    qInfo() << "PublishedNotify, media type:" << static_cast<int>(type);
    if(0 != code){
        QString msg = "发布默认资源失败！错误码：" + QString::number(code);
         QMessageBox::critical(NULL, "警告", msg, QMessageBox::Yes );
    } else {
        QMessageBox::information(NULL, "信息", "发布默认资源成功！", QMessageBox::Yes );
    }
}
void RtcMeetingModel::UnpublishedNotify(rcrtc::RCRTCMediaType type, int code){
    qInfo() << "UnpublishedNotify , media type:" << static_cast<int>(type);

    if(0 != code){
        QString msg = "取消发布默认资源失败！错误码：" + QString::number(code);
         QMessageBox::critical(NULL, "警告", msg, QMessageBox::Yes );
    } else {
        QMessageBox::information(NULL, "信息", "取消发布默认资源成功！", QMessageBox::Yes );
    }
}
void RtcMeetingModel::SubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code){
    qInfo() << "SubscribedNotify user id:"<< userId << ", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, "", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, 0==code);
    }
}
void RtcMeetingModel::UnsubscribedNotify(QString userId, rcrtc::RCRTCMediaType type, int code){
    qInfo() << "UnsubscribedNotify user id:"<< userId <<", media type:" << static_cast<int>(type);
    if(rcrtc::RCRTCMediaType::AUDIO_VIDEO == type
            || rcrtc::RCRTCMediaType::VIDEO == type){
        RemoteMediaInfo video(userId, "", rcrtc::RCRTCMediaType::VIDEO);
        NotifySubscribedStatus(video, false);
    }
}
void RtcMeetingModel::CustomStreamSubscribedNotify(QString userId,
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

void RtcMeetingModel::CustomStreamUnsubscribedNotify(QString userId,
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

void RtcMeetingModel::CreateEngineBtnClicked(){
    if(false == CheckingUserInformation()){
        return;
    }
    if(CreateEngine()){
        if(ConnectServer()){

        } else {
            QMessageBox::critical(NULL, "警告", "连接服务失败！", QMessageBox::Yes );
        }

    } else {
        QMessageBox::critical(NULL, "警告", "引擎创建失败！", QMessageBox::Yes );
    }

}
void RtcMeetingModel::DestroyEngineBtnClicked(){
    if(is_join_room_){
        QMessageBox::critical(NULL, "警告", "请先退出房间，在销毁RTC引擎！", QMessageBox::Yes );
        return;
    }
    if(false == DisconnectServer()){
        DestroyEngine();
    }
}
void RtcMeetingModel::EnterRoomBtnClicked(){
    if(false == EnterRoom()){
        QMessageBox::critical(NULL, "警告", "进入房间失败！", QMessageBox::Yes );
    }
}
void RtcMeetingModel::LeaveRoomBtnClicked(){
    if(false == LeaveRoom()){
        QMessageBox::critical(NULL, "警告", "离开房间失败！", QMessageBox::Yes );
    }
    ClearAllRemoteMediaInfo();
    ClearAllRemoteVIdeoRender();
    DetachLocalViewRender();
}
void RtcMeetingModel::PublishedStreamBtnClicked(){
    SetDefaultVideoConfig();
    if(false == PublishedStream()){
        QMessageBox::critical(NULL, "警告", "发布默认音视频资源失败！", QMessageBox::Yes );
    } else {
        AttachLocalViewRender();
    }
}
void RtcMeetingModel::UnpublisedStreamBtnClicked(){
    if(false == UnpublisedStream()){
        QMessageBox::critical(NULL, "警告", "取消发布默认音视频资源失败！", QMessageBox::Yes );
    } else {
        DetachLocalViewRender();
    }
}
void RtcMeetingModel::SubscribedStreamBtnClicked(){
    SubscribedStream();
}
void RtcMeetingModel::UnsubscribedBtnClicked(){
    Unsubscribed();
}
void RtcMeetingModel::PublishedShareBtnClicked(){
    if(false == PublishedShare()){
        QMessageBox::critical(NULL, "警告", "屏幕共享失败！", QMessageBox::Yes );
    }
}
void RtcMeetingModel::UnpublishedShareBtnClicked(){
    UnpublishedShare();
}

void RtcMeetingModel::connectSignals(){
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RoomJoinedSignal, this, &RtcMeetingModel::RoomJoinedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RoomLeftSignal, this, &RtcMeetingModel::RoomLeftNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserJoinedSignal, this, &RtcMeetingModel::UserJoinedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserOfflineSignal, this, &RtcMeetingModel::UserOfflineNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UserLeftSignal, this, &RtcMeetingModel::UserLeftNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemotePublishedSignal, this, &RtcMeetingModel::RemotePublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteUnpublishedSignal, this, &RtcMeetingModel::RemoteUnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteStateChangedSignal, this, &RtcMeetingModel::RemoteStateChangedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::PublishedSignal, this, &RtcMeetingModel::PublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UnpublishedSignal, this, &RtcMeetingModel::UnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::SubscribedSignal, this, &RtcMeetingModel::SubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::UnsubscribedSignal, this, &RtcMeetingModel::UnsubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamPublishedSignal, this, &RtcMeetingModel::RemoteCustomStreamPublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamUnpublishedSignal, this, &RtcMeetingModel::RemoteCustomStreamUnpublishedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamStateChangedSignal, this, &RtcMeetingModel::RemoteCustomStreamStateChangedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::RemoteCustomStreamFirstFrameSignal, this, &RtcMeetingModel::RemoteCustomStreamFirstFrameNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::CustomStreamSubscribedSignal, this,  &RtcMeetingModel::CustomStreamSubscribedNotify);
    connect(rcrtc_listener_impl_, &RcRtcListenerImpl::CustomStreamUnsubscribedSignal, this, &RtcMeetingModel::CustomStreamUnsubscribedNotify);
}
void RtcMeetingModel::disconnectSignals(){}
bool RtcMeetingModel::CheckingUserInformation()
{
    app_key_ = ConvertTostdString(ui->edit_rtc_appkey->text());
    token_ = ConvertTostdString(ui->edit_rtc_token->text());
    navigation_ = ConvertTostdString(ui->edit_rtc_navigation_url->text());
    room_id_ = ConvertTostdString(ui->edit_rtc_room_id->text());
    user_name_ = ConvertTostdString(ui->edit_rtc_UserName->text());
    if(app_key_.empty() || token_.empty() || navigation_.empty() || room_id_.empty() || user_name_.empty() ){
        QMessageBox::critical(NULL, "警告", "用户信息不完整", QMessageBox::Yes );
        return false;
    }
    return true;
}

void RtcMeetingModel::ModifyBtnStatus()
{
    ui->btn_create_engine->setEnabled(!is_engine_);
    ui->btn_destroy_engine->setEnabled(is_engine_);
    ui->btn_enter_room->setEnabled(is_engine_  && !is_join_room_);
    ui->btn_leave_room->setEnabled(is_engine_  && is_join_room_);
    ui->btn_published_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_unpublished_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_subscribed_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_unsubscribed_stream->setEnabled(is_engine_  && is_join_room_);
    ui->btn_published_share->setEnabled(is_engine_  && is_join_room_);
    ui->btn_unpublished_share->setEnabled(is_engine_  && is_join_room_);
}

bool RtcMeetingModel::CreateEngine(){
    int32_t error_code = -1;
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

bool RtcMeetingModel::DestroyEngine(){
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
bool RtcMeetingModel::ConnectServer(){
    if(0 == rcim_set_connection_callback(handle_im_, RcsdkConnectionStatusCB, this)){
        if(0 == rcim_connect(handle_im_, token_.c_str())){
            return true;
        }
    }
    return false;
}
bool RtcMeetingModel::DisconnectServer(){
    if(0 == rcim_disconnect(handle_im_)){
        return true;
    }
    return false;
}

bool RtcMeetingModel::EnterRoom(){
    int32_t ret =-1;
    rcrtc::RCRTCRoomSetup* setup = rcrtc::RCRTCRoomSetup::create();
    if(nullptr == setup){
        ret = rcrtc_engine_->joinRoom(room_id_);
    } else {
        setup->setRole(rcrtc::RCRTCRole::MEETING_MEMBER);
        setup->setJoinType(rcrtc::RCRTCJoinType::KICK_OTHER_DEVICE);
        setup->setMediaType(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
        ret = rcrtc_engine_->joinRoom(room_id_,setup);
        rcrtc::RCRTCRoomSetup::destroy(&setup);
    }
    return ret == 0;
}
bool RtcMeetingModel::LeaveRoom(){
    int32_t ret = rcrtc_engine_->leaveRoom();
    return ret == 0;
}

bool RtcMeetingModel::SetDefaultVideoConfig()
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
    int32_t err_code = rcrtc_engine_->setVideoConfig(config);
    rcrtc::RCRTCVideoConfig::destroy(&config);
    if(err_code !=0) {
        qCritical() << "set video config failed.";
    }
    return 0 == err_code;
}

bool RtcMeetingModel::PublishedStream(){
    if(nullptr == rcrtc_engine_){
        return false;
    }
    int32_t ret = rcrtc_engine_->publish(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
    return 0 == ret;
}
bool RtcMeetingModel::UnpublisedStream()
{
    if(nullptr == rcrtc_engine_){
        return false;
    }
    int32_t ret = rcrtc_engine_->unpublish(rcrtc::RCRTCMediaType::AUDIO_VIDEO);
    return 0 == ret;
}

void RtcMeetingModel::SubscribedStream(){
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
void RtcMeetingModel::Unsubscribed(){
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

bool RtcMeetingModel::PublishedShare(){
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
    int32_t maxBit;
    int32_t minBit;
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

bool RtcMeetingModel::UnpublishedShare(){
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

void RtcMeetingModel::InsterRemoteVideoRender(const RemoteMediaInfo&  media_info,  RemoteStreamType type){
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
void RtcMeetingModel::RemoveRemoteVideoRender(const RemoteMediaInfo&  media_info){
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

void RtcMeetingModel::RemoveRemoteVideoRender(const QString &user_id)
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
void RtcMeetingModel::ClearAllRemoteVIdeoRender()
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

void RtcMeetingModel::NotifySubscribedStatus(const RemoteMediaInfo &media_info, bool is_subscribed)
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

void RtcMeetingModel::InsterRemoteMediaInfo(const RemoteMediaInfo&  media_info){
    QWriteLocker locker(&mutex_remote_media_);
    if(media_info.stream_tag_ == ""){
        remote_media_list_.push_back(media_info);
    } else {
        remote_custom_media_list_.push_back(media_info);
    }
}
void RtcMeetingModel::RemoveRemoteMediaInfo(const RemoteMediaInfo&  media_info){
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

void RtcMeetingModel::RemoveRemoteMediaInfo(const QString &user_id)
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
}
void RtcMeetingModel::ClearAllRemoteMediaInfo()
{
    QWriteLocker locker(&mutex_remote_media_);
    auto it = remote_media_list_.begin();
    while(it != remote_media_list_.end()){
        it = remote_media_list_.erase(it);
    }
    it = remote_custom_media_list_.begin();
    while(it != remote_custom_media_list_.end()){
        it = remote_custom_media_list_.erase(it);
    }
}

void RtcMeetingModel::AttachLocalViewRender(){
    if(nullptr == rcrtc_engine_){
        return;
    }
    HANDLE viewId = (HANDLE)ui->widget_local_view->winId();
    view_render_ = rcrtc::IRCRTCView::create((HANDLE)viewId);
    view_render_->setMirror(false);
    view_render_->setFitType(rcrtc::RCRTCViewFitType::FIT);
    rcrtc_engine_->setLocalView(view_render_);
}
void RtcMeetingModel::DetachLocalViewRender(){
    if(nullptr == rcrtc_engine_ || nullptr ==view_render_){
        return;
    }
    rcrtc_engine_->removeLocalView();
    rcrtc::IRCRTCView::destroy(&view_render_);
    QString  style = "QWidget{background-color:black;};";
    ui->widget_local_view->setStyleSheet(style);
}
