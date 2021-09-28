#ifndef LIVE_H
#define LIVE_H

#include <QWidget>
#include <qmutex.h>

#include <rcim.h>
#include <libc_rcrtc.h>
#include <libc_rtc_types.h>

#include "remoteuserui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Live; }
QT_END_NAMESPACE

class RCLive : public QWidget
{
    Q_OBJECT

public:
    RCLive(QWidget *parent = nullptr);
    ~RCLive();
    bool event(QEvent *event);

    void dispost();

private slots:
    static void subscribeCb(enum_rcrtc_code code, HANDLE context);
    void subscribe(const QString& id);
    void setupRenderAndGatherStreams(const QString& id, std::vector<HANDLE_STREAM>& streams);
    void subscribeAllUsers();
    void unsubscribeAllUsers();

    static void unsubscribeCb(enum_rcrtc_code code, HANDLE context);
    void unsubscribe(const QString& id);
    void removeVideoRender(const QString& userId);
    void gatherRemoteStreams(std::vector<HANDLE_STREAM>& gathered_streams);

    static void connectCb(HANDLE context, rc_connection_status code);
    void connect();

    void release();
    void disconnect();

    static void roomCb(const char *room_id, const char *remote_user, enum_rcrtc_room_event code, void *event_param, HANDLE context);
    static void joinRoomCb(const char *room_id, enum_rcrtc_code code, HANDLE context);
    void joinRoom();

    static void leaveRoomCb(enum enum_rcrtc_code code, HANDLE context);
    void leaveRoom();

    static void publishCb(enum_rcrtc_code code, HANDLE context);
    void publish();

    static void unpublishCb(enum_rcrtc_code code, HANDLE context);
    void unpublish();

    void slot_toggled_audience(bool toggled);
    void slot_toggled_anchor(bool toggled);

    void slot_mix_streams();

private:
    void OpenVideoCaptureDevice(int index = 0);
    void CloseVideoCaptureDevice();
    void ListVideoCapture();

    void ListAudioDevice();
    void OpenMicSpkDevice();
    void CloseMicSpkDevice();

    bool IsExistRemoteUserUI(const QString& userId);
    void RemoveRemoteUserUI(const QString& userId);
    RemoteUserUI* CreateRemoteUserUI(const QString& userId);

    void SetLiveRole(bool is_anchor);

private:
    Ui::Live *ui;

    rcrtc_video_canvas_t _localVideoView;

    QMutex _mtxRemoteUserWidgetList;
    QHash<QString, RemoteUserUI*> _remoteUserWidgetList;
    QHash<QString, void*> _userList;

    bool _isConnected = false;
    bool _isInRoom = false;
    bool _isPublish = false;
    bool _isStartVideoDevice = false;

    QString _appKey;
    QString _token;
    QString _roomId;
    QString _lastRemoteId;

    // rcim 引擎句柄
    HANDLE _rcim_engine;
    // 当前摄像头
    int _index_camera = -1;
    // 当前摄像头属性
    int _index_capability = -1;
    // 当前麦克风(mic)
    uint16_t _index_mic = -1;
    // 当前扬声器(spk)
    uint16_t _index_spk = -1;

    uint32_t _current_role = 0;
};
#endif // LIVE_H
