#include "live.h"
#include "./ui_live.h"


#include <QDebug>
#include <QLineEdit>
#include <QListWidgetItem>

#include "mix_streams_layout.h"

static const char* g_navi_url_ = "nav.cn.ronghub.com";


//房间内用户相关数据
typedef struct RemoteUser {
    int stream_count; //用户发布的流个数
    HANDLE_STREAM streams[64]; //用户发布的流 ID
    RemoteUserUI *ui; //用户的视频预览窗口句柄
    rcrtc_video_canvas_t render; //用户的视频渲染句柄
}RemoteUser;

//建立连接成功
static const QEvent::Type EventConnect = static_cast<QEvent::Type>(9999);
//用户加入房间
static const QEvent::Type EventUserJoin = static_cast<QEvent::Type>(10000);
//用户离开房间
static const QEvent::Type EventUserLeave = static_cast<QEvent::Type>(10001);
//加入房间成功
static const QEvent::Type EventJoinRoom = static_cast<QEvent::Type>(10002);
//离开房间成功
static const QEvent::Type EventLeaveRoom = static_cast<QEvent::Type>(10003);
//发布流成功
static const QEvent::Type EventPublish = static_cast<QEvent::Type>(10004);
//取消发布流成功
static const QEvent::Type EventUnpublish = static_cast<QEvent::Type>(10005);
//订阅房间内所有用户
static const QEvent::Type EventSubscribeAll = static_cast<QEvent::Type>(10006);


class RtcEvent : public QEvent {
public:
    QString id;
    RtcEvent(QEvent::Type type, QString id_) : QEvent(type), id(id_){}
};

RCLive::RCLive(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Live)
{
    ui->setupUi(this);
    ui->local_video_view->setStyleSheet("background-color:black;");
    QObject::connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(connect()));

    QString appKey = "";
    QString roomId = "";
    QString token = "";
    QString userName = "";
    QString naviUrl = g_navi_url_;

    ui->lineEdit_appKey->setText(appKey);
    ui->lineEdit_roomId->setText(roomId);
    ui->lineEdit_token->setText(token);
    ui->lineEdit_userName->setText(userName);
    ui->lineEdit_navi_url->setText(naviUrl);

    QObject::connect(ui->radioButton_audience, SIGNAL(clicked(bool)), this, SLOT(slot_toggled_audience(bool)));
    QObject::connect(ui->radioButton_anchor, SIGNAL(clicked(bool)), this, SLOT(slot_toggled_anchor(bool)));
    QObject::connect(ui->pushButton_mix_stream, SIGNAL(clicked()), this, SLOT(slot_mix_streams()));

    SetLiveRole(true);
}

RCLive::~RCLive()
{
    release();
    rcrtc_disable_video();
    rcrtc_disable_audio();

    delete ui;
}

void RCLive::SetLiveRole(bool is_anchor)
{
    if (is_anchor)
    {
        _current_role = RCRTC_LIVE_ROLE_ANCHOR;
    }
    else
    {
        _current_role = RCRTC_LIVE_ROLE_AUDIENCE;
    }
    ui->pushButton_mix_stream->setEnabled(is_anchor);
    ui->radioButton_anchor->setChecked(is_anchor);
    ui->radioButton_audience->setChecked(!is_anchor);
}

void RCLive::slot_toggled_audience(bool toggled)
{
    SetLiveRole(false);
}

void RCLive::slot_toggled_anchor(bool toggled)
{
    SetLiveRole(true);
}

bool RCLive::event(QEvent *event)
{
    static int count = 0;
    RtcEvent *e = (RtcEvent*)event;
    switch (e->type()) {
    case EventConnect: //建立连接成功后，执行加入房间
        joinRoom();
        break;
    case EventJoinRoom: //加入房间成功后，开始发布音视频流
        publish();
        break;
    case EventPublish: //发布成功后，更新 UI 的状态
        ui->pushButton_connect->setEnabled(true);
        ui->pushButton_connect->setText("disconnect");
        break;
    case EventLeaveRoom: //离开房间成功后，执行释放资源
        release();
        break;
    case EventUnpublish: //取消发布成功后，执行离开房间
        leaveRoom();
        break;
    case EventUserJoin: //有用户加入房间后，开始订阅用户发布的流
        _lastRemoteId = e->id;
        subscribe(e->id);
        break;
    case EventUserLeave: //有用户离开房间后，开始释放用户相关的资源
        unsubscribe(e->id);
        break;
    case EventSubscribeAll: //尝试订阅房间内所有用户发布的流
        subscribeAllUsers();
        break;
    default:
        QWidget::event(event);
    }
    return true;
}

//订阅的状态回调
void RCLive::subscribeCb(enum_rcrtc_code code, HANDLE context)
{
    if (code != 0){
        qDebug() << "subscribeCb error: " << code;
    }
}

bool RCLive::IsExistRemoteUserUI(const QString& userId)
{
    if (!userId.isEmpty())
    {
        QMutexLocker lock(&_mtxRemoteUserWidgetList);
        if(_remoteUserWidgetList.contains(userId))
        {
            return true;
        }
    }
    return false;
}

void RCLive::RemoveRemoteUserUI(const QString& userId)
{
    if (IsExistRemoteUserUI(userId))
    {
        QMutexLocker lock(&_mtxRemoteUserWidgetList);
        RemoteUserUI* userWidget = _remoteUserWidgetList.value(userId);
        QListWidgetItem *userItem = userWidget->getItem();
        delete userItem;
        delete userWidget;
        _remoteUserWidgetList.remove(userId);
    }
}

RemoteUserUI* RCLive::CreateRemoteUserUI(const QString& userId)
{
    if(userId.isEmpty() || IsExistRemoteUserUI(userId))
    {
        return nullptr;
    }

    QListWidgetItem *userItem = new QListWidgetItem(ui->listWidget_remoteUser);
    RemoteUserUI* userWidget = new RemoteUserUI();
    userWidget->setItem(userItem);
    userItem->setSizeHint(userWidget->size());
    ui->listWidget_remoteUser->addItem(userItem);
    ui->listWidget_remoteUser->setItemWidget(userItem, userWidget);
    QMutexLocker lock(&_mtxRemoteUserWidgetList);
    _remoteUserWidgetList[userId] = userWidget;
    return userWidget;
}

//订阅指定的用户
void RCLive::subscribe(const QString& userId)
{
    //创建视频流渲染相关的资源
    RemoteUserUI* userWidget = CreateRemoteUserUI(userId);
    if (!userWidget)
    {
        return;
    }

    RemoteUser *remote_user = new RemoteUser();
    memset(remote_user, 0, sizeof(RemoteUser));
    remote_user->ui = userWidget;

    HANDLE_STREAM tinyStreams[64] = {0};

    int count = 0;
    HANDLE_STREAM stream_user[64] = {0};
    //获取房间内远端用户 remote_user_id 所有发布的流
    if (rcrtc_remote_user_get_streams(_roomId.toUtf8().constData(), userId.toUtf8().constData(), stream_user, &count) == 0) {
        for (int j = 0; j < count; j++) {
            enum_rcrtc_stream_mediatype media_type = RCRTC_STREAM_MEDIA_UNKNOWN;
            //获取当前流的媒体类型
            if (rcrtc_stream_get_media_type(stream_user[j], &media_type) != 0) {
                qDebug("rcrtc_stream_get_media_type() failed\n");
                continue;
            }

            if (RCRTC_STREAM_MEDIA_VIDEO == media_type) {
                //为视频流设置渲染句柄
                WId wid = userWidget->winId();
                remote_user->streams[remote_user->stream_count] = stream_user[j];
                remote_user->stream_count++;
                remote_user->render.view = (HWND)wid;
                remote_user->render.video_mirror = false;
                remote_user->render.video_fill_mode = RCRTC_VIDEO_FILL_MODE_STRETCH_FIT;
                strncpy(remote_user->render.uid, userId.toUtf8().constData(), userId.length());
                rcrtc_setup_video_stream(stream_user[j], &remote_user->render);

            }else if (RCRTC_STREAM_MEDIA_AUDIO == media_type){
                remote_user->streams[remote_user->stream_count] = stream_user[j];
                remote_user->stream_count++;
            }
        }
        rcrtc_subscribe_streams(_roomId.toUtf8().constData(), remote_user->streams, tinyStreams, subscribeCb, this);
    }

    _userList[userId] = remote_user;

}

void RCLive::setupRenderAndGatherStreams(const QString& userId, std::vector<HANDLE_STREAM>& streams)
{
    //创建视频流渲染相关的资源
    RemoteUserUI* userWidget = CreateRemoteUserUI(userId);
    if (!userWidget)
    {
        return;
    }

    RemoteUser *remote_user = new RemoteUser();
    memset(remote_user, 0, sizeof(RemoteUser));
    remote_user->ui = userWidget;

    //    HANDLE_STREAM tinyStreams[64] = {0};

    int count = 0;
    HANDLE_STREAM stream_user[64] = {0};
    //获取房间内远端用户 remote_user_id 所有发布的流
    if (rcrtc_remote_user_get_streams(_roomId.toUtf8().constData(), userId.toUtf8().constData(), stream_user, &count) == 0) {
        for (int j = 0; j < count; j++) {
            enum_rcrtc_stream_mediatype media_type = RCRTC_STREAM_MEDIA_UNKNOWN;
            //获取当前流的媒体类型
            if (rcrtc_stream_get_media_type(stream_user[j], &media_type) != 0) {
                qDebug("rcrtc_stream_get_media_type() failed\n");
                continue;
            }

            if (RCRTC_STREAM_MEDIA_VIDEO == media_type) {
                //为视频流设置渲染句柄
                WId wid = userWidget->winId();
                remote_user->streams[remote_user->stream_count] = stream_user[j];
                streams.push_back(stream_user[j]);
                remote_user->stream_count++;
                remote_user->render.view = (HWND)wid;
                remote_user->render.video_mirror = false;
                remote_user->render.video_fill_mode = RCRTC_VIDEO_FILL_MODE_STRETCH_FIT;
                strncpy(remote_user->render.uid, userId.toUtf8().constData(), userId.length());
                rcrtc_setup_video_stream(stream_user[j], &remote_user->render);

            }else if (RCRTC_STREAM_MEDIA_AUDIO == media_type){
                remote_user->streams[remote_user->stream_count] = stream_user[j];
                streams.push_back(stream_user[j]);
                remote_user->stream_count++;
            }
        }
    }

    _userList[userId] = remote_user;
}

//订阅房间内所有用户
void RCLive::subscribeAllUsers()
{
    char remote_users[256][256] = {{0}};
    if (rcrtc_room_get_remote_users(_roomId.toUtf8().constData(), remote_users) != 0) {
        qDebug("rcrtc_room_get_remote_users() failed\n");
        return;
    }

    std::vector<HANDLE_STREAM> streams;
    for (int i = 0; i < 256; i++) {
        if ((remote_users[i][0] == '\0')) {
            break;
        }
        setupRenderAndGatherStreams(remote_users[i], streams);
    }

    int index = 0;
    HANDLE_STREAM normStreams[64] = {0};
    HANDLE_STREAM tinyStreams[64] = {0};
    for (auto it = streams.begin();it != streams.end() ; it++) {
        normStreams[index++] = *it;
    }
    rcrtc_subscribe_streams(_roomId.toUtf8().constData(), normStreams, tinyStreams, subscribeCb, this);
}

//取消订阅房间内所有用户
void RCLive::unsubscribeAllUsers()
{
    std::vector<HANDLE_STREAM> gathered_streams;
    gatherRemoteStreams(gathered_streams);

    int index = 0;
    HANDLE_STREAM streams[64] = {0};
    for (auto it = gathered_streams.begin();it != gathered_streams.end() ; it++) {
        streams[index++] = *it;
    }
    rcrtc_unsubscribe_streams(_roomId.toUtf8().constData(), streams, unsubscribeCb, this);

    QList<QString> list = _userList.keys();
    for(int i=0;i<list.length();i++){
        removeVideoRender(list[i]);
    }
}

//取消订阅的状态回调
void RCLive::unsubscribeCb(enum_rcrtc_code code, HANDLE context)
{
    if (code != 0){
        qDebug() << "unsubscribeCb error: " << code;
    }
}

//取消订阅指定的用户
void RCLive::unsubscribe(const QString& userId)
{
    RemoteUser *ru = (RemoteUser *)_userList[userId];
    RemoteUserUI* userWidget = ru->ui;
    QListWidgetItem *userItem = userWidget->getItem();

    rcrtc_unsubscribe_streams(_roomId.toUtf8().constData(), ru->streams, unsubscribeCb, this);
    ru->render.view = nullptr;
    rcrtc_setup_video_stream(ru->streams[0], &ru->render);

    ui->listWidget_remoteUser->removeItemWidget(userItem);
    delete userItem;
    delete userWidget;
    delete ru;
}

void RCLive::removeVideoRender(const QString& userId)
{
    RemoteUser *ru = (RemoteUser *)_userList[userId];
    RemoteUserUI* userWidget = ru->ui;
    QListWidgetItem *userItem = userWidget->getItem();

    ru->render.view = nullptr;
    rcrtc_setup_video_stream(ru->streams[0], &ru->render);

    ui->listWidget_remoteUser->removeItemWidget(userItem);
    RemoveRemoteUserUI(userId);
    delete ru;
    _userList.remove(userId);
}

void RCLive::gatherRemoteStreams(std::vector<HANDLE_STREAM>& gathered_streams)
{
    for (auto it = _userList.begin(); it != _userList.end(); it++) {
        int streams_count = ((RemoteUser *)it.value())->stream_count;
        HANDLE_STREAM* streams = ((RemoteUser *)it.value())->streams;
        for (int i = 0; i < streams_count; i++) {
            gathered_streams.push_back(streams[i]);
        }
    }
}

//建立连接的状态回调
void RCLive::connectCb(HANDLE context, rc_connection_status code)
{
    RCLive *model = (RCLive *)context;
    QCoreApplication::postEvent(model, new RtcEvent(EventConnect, ""));
}

//建立连接
void RCLive::connect()
{
    if (!_isConnected){

        _appKey = ui->lineEdit_appKey->text();
        if (_appKey.isEmpty()){
            qDebug("invalid app key\n");
            return;
        }

        _token = ui->lineEdit_token->text();
        if (_token.isEmpty()){
            qDebug("invalid token\n");
            return;
        }

        _roomId = ui->lineEdit_roomId->text();
        if (_roomId.isEmpty()){
            qDebug("invalid room id\n");
            return;
        }

        _isConnected = true;
        ui->pushButton_connect->setDisabled(true);

        QString str_navi_url = g_navi_url_;
        QString input_navi_url = ui->lineEdit_navi_url->text();
        if (!input_navi_url.isEmpty())
        {
            str_navi_url = input_navi_url;
        }
        //初始化 IM
        _rcim_engine = rcim_init(_appKey.toUtf8().constData(), str_navi_url.toUtf8().constData(), "./", nullptr);
        if (_rcim_engine == nullptr) {
            qDebug("rcim_init failed.\n");
        }

        //初始化 RTC
        int error_code = rcrtc_init(_rcim_engine);
        if (error_code != 0) {
            qDebug("rcrtc_init failed. error code=%d\n", error_code);
        }

        rcrtc_config_t config;
        memset(&config, 0, sizeof(rcrtc_config_t));
        config.enable_srtp = false;
        int ret = rcrtc_set_config(&config);
        if (ret < 0) {
            qDebug("rcrtc_set_config error %d\n", ret);
        }

        //初始化视频设备
        ListVideoCapture();

        WId wid = (WId)ui->local_video_view->winId();
        _localVideoView.view = (RCView) wid;
        _localVideoView.video_fill_mode = RCRTC_VIDEO_FILL_MODE_STRETCH_FIT;
        _localVideoView.video_mirror = true;
        strncpy_s(_localVideoView.uid, "me", strlen("me"));
        ret = rcrtc_video_capture_attach_local_video(&_localVideoView);
        if (ret != 0) {
            qDebug("Error: setup local video failed.\n");
        }

        OpenVideoCaptureDevice();

        //初始化音频设备
        ListAudioDevice();
        OpenMicSpkDevice();

        //设置连接状态回调
        ret = rcim_set_connection_callback(_rcim_engine, connectCb, this);
        if (ret < 0) {
            qDebug("rcim_set_connection_callback failed %d\n", ret);
        }

        //建立连接
        ret = rcim_connect(_rcim_engine, _token.toUtf8().constData());
        if (ret < 0) {
            qDebug("rcim_connect failed %d\n", ret);
        }

    }else {

        //取消连接并释放资源
        ui->pushButton_connect->setDisabled(true);
        if (_isInRoom){
            if (_isPublish){
                unpublish();
            }else {
                leaveRoom();
            }
        }else {
            release();
        }
    }
}

//断开连接并释放资源
void RCLive::release()
{
    _isConnected = false;

    //取消订阅所有用户
    unsubscribeAllUsers();

    //断开连接
    rcim_disconnect(_rcim_engine);
    //关闭音频设备
    CloseMicSpkDevice();
    //关闭视频设备
    CloseVideoCaptureDevice();
    //释放渲染句柄
    int32_t ret = rcrtc_video_capture_dettach_local_video((RCView)_localVideoView.view);
    if (ret != 0) {
        qDebug("Error: setup local video failed.\n");
    }

    //更新 UI
    ui->local_video_view->setStyleSheet("background-color:black;");
    ui->pushButton_connect->setText("connect");
    ui->pushButton_connect->setEnabled(true);
}

//断开连接
void RCLive::disconnect()
{
    if (_isConnected){
        ui->pushButton_connect->setDisabled(true);
        //是否加入了房间
        if (_isInRoom){
            //是否发布了流
            if (_isPublish){
                //如果发布了流，就执行取消发布的操作，在取消发布的状态回调中执行离开房间的操作
                unpublish();
            }else {
                //如果加入了房间，就执行离开房间，在离开房间的状态回调中释放资源
                leaveRoom();
            }
        }else {
            //如果尚未加入房间，就直接断开连接，释放资源
            release();
        }
    }
}

//房间状态回调
void RCLive::roomCb(const char *room_id, const char *remote_user, enum_rcrtc_room_event code, void *event_param, HANDLE context)
{
    RCLive *model = (RCLive *)context;
    if (RTC_ROOM_EVENT_REMOTE_USER_JOINED == code) {
        //有用户加入房间
        qDebug("cb_room_event:RTC_ROOM_EVENT_REMOTE_USER_JOINED %s joined\n", remote_user);
    } else if (RTC_ROOM_EVENT_REMOTE_USER_LEFT == code) {
        //有用户离开房间
        qDebug("cb_room_event:RTC_ROOM_EVENT_REMOTE_USER_LEFT %s leave\n", remote_user);
        QCoreApplication::postEvent(model, new RtcEvent(EventUserLeave, remote_user));
    } else if (RTC_ROOM_EVENT_REMOTE_USER_STREAM_PUBLISHED == code) {
        //有用户发布了流
        qDebug("cb_room_event:RTC_ROOM_EVENT_REMOTE_USER_STREAM_PUBLISHED %s publish\n", remote_user);
        QCoreApplication::postEvent(model, new RtcEvent(EventUserJoin, remote_user));
    } else if (RTC_ROOM_EVENT_REMOTE_USER_STREAM_UNPUBLISHED == code) {
        //有用户取消发布
        qDebug("cb_room_event:RTC_ROOM_EVENT_REMOTE_USER_STREAM_UNPUBLISHED %s unpublish\n", remote_user);
    }
}

//加入房间的状态回调
void RCLive::joinRoomCb(const char *room_id, enum_rcrtc_code code, HANDLE context)
{
    RCLive *model = (RCLive *)context;
    QCoreApplication::postEvent(model, new RtcEvent(EventJoinRoom, ""));
    QCoreApplication::postEvent(model, new RtcEvent(EventSubscribeAll, ""));

    int ret = rcrtc_set_room_event_callback(roomCb, context);
    if (ret != 0) {
        return;
    }
}

//加入房间
void RCLive::joinRoom()
{
    if (_isConnected && !_isInRoom){
        _isInRoom = true;
        rcrtc_room_config_t cfg;
        cfg.room_type = RCRTC_ROOM_TYPE_AUDIO_VIDEO;
        cfg.live_role = (enum_rcrtc_live_role)_current_role;
        int ret = rcrtc_join_room(_roomId.toUtf8().constData(), cfg, joinRoomCb, this);
        if (ret < 0) {
            qDebug("rcrtc_join_room failed\n");
            return;
        }
    }
}

//离开房间的状态回调
void RCLive::leaveRoomCb(enum enum_rcrtc_code code, HANDLE context)
{
    RCLive *model = (RCLive *)context;
    QCoreApplication::postEvent(model, new RtcEvent(EventLeaveRoom, ""));
}


//离开房间
void RCLive::leaveRoom()
{
    if (_isInRoom){
        _isInRoom = false;
        int ret = rcrtc_leave_room(_roomId.toUtf8().constData(), leaveRoomCb, this);
        if (ret != 0) {
            qDebug("rcrtc_leave_room() failed\n");
            return;
        }
    }
}

//发布流的状态回调
void RCLive::publishCb(enum_rcrtc_code code, HANDLE context)
{
    qDebug() << "publishCb: " << code;
    RCLive *model = (RCLive *)context;
    QCoreApplication::postEvent(model, new RtcEvent(EventPublish, ""));
}

//发布流
void RCLive::publish()
{
    if (!_isPublish){
        _isPublish = true;
        HANDLE_STREAM streams[256] = {0};
        streams[0] = rcrtc_get_default_audio_stream();
        streams[1] = rcrtc_get_default_video_stream();
        int ret = rcrtc_publish_streams(streams, publishCb, this);
        if (ret < 0) {
            qDebug("rcrtc_publish_default_streams() failed\n");
        }
    }
}

//取消发布流的状态回调
void RCLive::unpublishCb(enum_rcrtc_code code, HANDLE context)
{
    qDebug() << "unpublishCb: " << code;
    RCLive *model = (RCLive *)context;
    QCoreApplication::postEvent(model, new RtcEvent(EventUnpublish, ""));
}

//取消发布流
void RCLive::unpublish()
{
    if (_isPublish){
        _isPublish = false;
        HANDLE_STREAM streams[256] = {0};
        streams[0] = rcrtc_get_default_audio_stream();
        streams[1] = rcrtc_get_default_video_stream();
        if (rcrtc_unpublish_streams(streams, unpublishCb, this) < 0){
            qDebug("rcrtc_unpublish_video_streams() failed\n");
        }
    }
}


/*
 * @brief 枚举设备摄像头输入设备
 */
void RCLive::ListVideoCapture() {
    //@ 创建摄像头枚举句柄
    HANDLE_DEVICE_INFO device_info = rcrtc_video_capture_create_device_info();
    if (device_info == NULL) {
        qDebug("Error: CreateDeviceInfo failed \n");
        return;
    }
    char device_name[256];
    char unique_name[256];
    char product_name[256];
    int ret = 0;
    //@ 得到可用摄像头个数
    int device_number = rcrtc_video_capture_get_device_number(device_info);
    qDebug("Device Info: number = %d\n", device_number);
    if (device_number == 0) {
        //@ 销毁摄像头枚举句柄
        rcrtc_video_capture_destroy_device_info(device_info);
        return;
    }
    for (int i = 0; i < device_number; ++i) {
        memset(device_name, 0, 256);
        memset(unique_name, 0, 256);
        memset(product_name, 0, 256);
        ret = rcrtc_video_capture_get_device_name(
                    device_info, i, device_name, sizeof(device_name), unique_name,
                    sizeof(unique_name), product_name, sizeof(product_name));
        if (ret != 0) {
            qDebug("Error: GetDeviceName failed, ret = %d \n", ret);
            //@ 销毁摄像头枚举句柄
            rcrtc_video_capture_destroy_device_info(device_info);
            return;
        }

    }
    // 默认取位置0的摄像头和相应属性位置
    _index_camera = (device_number > 0) ? 0 : -1;
    _index_capability = 0;
    //@ 销毁摄像头枚举句柄
    rcrtc_video_capture_destroy_device_info(device_info);
}

/*
 * @brief 打开本地本地摄像头设备
 */
void RCLive::OpenVideoCaptureDevice(int index) {
    if (!_isStartVideoDevice){
        if (index < 0) {
            qDebug("Error: EnableVideo index_camera error\n");
            return;
        }
        //@ 启用指定的摄像头设备
        int ret =
                rcrtc_enable_video(index);
        if (ret != 0) {
            qDebug("Error: rcrtc_enable_video() failed\n");
        }
        _isStartVideoDevice = true;
    }
}

/*
 * @brief 关闭本地本地摄像头设备
 */
void RCLive::CloseVideoCaptureDevice() {
    if (_isStartVideoDevice){
        _isStartVideoDevice = false;
        int ret = rcrtc_disable_video();
        if (ret != 0) {
            qDebug("Error: rcrtc_disable_video failed \n");
        }
    }
}

/*
 * @brief  枚举设备输入设备, 设置当前默认使用的麦克风(mic)扬声器(spk)设备
 * @TODO():
 */
void RCLive::ListAudioDevice() {
    int ret = 0;
    if ((ret = rcrtc_audio_device_init()) != 0) {
        qDebug("rcrtc_audio_device_intialize failed error = %d\n", ret);
        return;
    }
    int16_t num_speaker = 0;
    if ((num_speaker = rcrtc_audio_device_get_speaker_num()) < 0) {
        qDebug("rcrtc_audio_device_get_speaker_num failed error = %d\n",
               num_speaker);
    }
    int16_t num_mic = 0;
    if ((num_mic = rcrtc_audio_device_get_microphone_num()) < 0) {
        qDebug("rcrtc_audio_device_get_microphone_num failed error = %d\n",
               num_mic);
    }
    char name[MAX_DEVICE_NAME_SIZE] = {0};
    for (int16_t i = 0; i < num_speaker; i++) {
        if ((ret = rcrtc_audio_device_get_speaker_name(i, name)) < 0) {
            qDebug("rcrtc_audio_device_get_speaker_name failed error = %d\n", ret);
            continue;
        }
        qDebug("rcrtc_audio_device_get_speaker_name %s\n", name);
        if ((ret = rcrtc_audio_device_set_speaker_index(i)) < 0) {
            qDebug("rcrtc_audio_device_get_speaker_min_max_volume failed error = %d\n", ret);
        }
        if ((ret = rcrtc_audio_device_set_speaker_volume(100)) < 0) {
            qDebug("rcrtc_audio_device_set_speaker_volume %d\n", ret);
        }
    }

    for (int16_t i = 0; i < num_mic; i++) {
        if ((ret = rcrtc_audio_device_get_microphone_name(i, name)) < 0) {
            qDebug("rcrtc_audio_device_get_microphone_name failed error = %d\n", ret);
            continue;
        }
        qDebug("rcrtc_audio_device_get_microphone_name %s\n", name);
        if ((ret = rcrtc_audio_device_set_microphone_index(0)) < 0) {
            qDebug("rcrtc_audio_device_set_microphone_device failed error = %d\n", ret);
        }
        if ((ret = rcrtc_audio_device_set_microphone_volume(100)) <
                0) {
            qDebug("rcrtc_audio_device_set_microphone_volume %d\n", ret);
        }
    }
    rcrtc_audio_device_uninit();

    // 默认取位置0的mic
    if (num_mic > 0) {
        _index_mic = 0;
    }
    if (num_speaker > 0) {
        _index_spk = 0;
    }
}

/*
 * @brief 打开本地麦克风和扬声器设备
 */
void RCLive::OpenMicSpkDevice() {
    //@ 启用麦克风(mic)扬声器(spk)设备
    rcrtc_audio_device_set_microphone_index(_index_mic);
    rcrtc_audio_device_set_speaker_index(_index_spk);
    int ret = rcrtc_enable_audio();
    if (ret != 0) {
        qDebug("Error: rcrtc_enable_audio failed \n");
        return;
    }
}

/*
 * @brief 关闭本地麦克风和扬声器设备
 */
void RCLive::CloseMicSpkDevice() {
    //@ 禁用麦克风(mic)扬声器(spk)设备
    rcrtc_disable_audio();
}

/*
 * @brief 合流布局
 */
void RCLive::slot_mix_streams() {
    int32_t ret = 0;
    char userId[256] = {0};
    if (_rcim_engine) {
        ret = rcim_get_user_id(_rcim_engine, userId, 256);
        if (ret != 0){
            return;
        }
        QString room_id = ui->lineEdit_roomId->text();
        std::string local_user_id = userId;
        std::string remote_user_id = _lastRemoteId.toStdString();
        if (remote_user_id.empty()) {
            remote_user_id = local_user_id;
        }
        rc_mix_test::MixStreamsLayoutDemo mix_demo;
        mix_demo.MixStreamLayout(room_id.toStdString(), local_user_id, remote_user_id);
    }
}

void RCLive::dispost(){
    disconnect();
}
