#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <rcim.h>
#include <libc_rcrtc.h>
#include <libc_rtc_types.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool event(QEvent *event);

private slots:
    static void subscribeCb(enum_rcrtc_code code, HANDLE context);
    void subscribe(QString id);
    void subscribeAllUsers();
    void unsubscribeAllUsers();

    static void unsubscribeCb(enum_rcrtc_code code, HANDLE context);
    void unsubscribe(QString id);

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

private:
    void OpenVideoCaptureDevice(int index = 0);
    void CloseVideoCaptureDevice();
    void ListVideoCapture();

    void ListAudioDevice();
    void OpenMicSpkDevice();
    void CloseMicSpkDevice();

private:
    Ui::MainWindow *ui;

    rcrtc_video_canvas_t _localVideoView;

    QHash<QString, void*> _widgetList;
    QHash<QString, void*> _userList;

    bool _isConnected = false;
    bool _isInRoom = false;
    bool _isPublish = false;
    bool _isStartVideoDevice = false;


    QString _appKey;
    QString _token;
    QString _roomId;

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
};
#endif // MAINWINDOW_H
