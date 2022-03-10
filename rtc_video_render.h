#ifndef RTC_VIDEO_RENDER_H
#define RTC_VIDEO_RENDER_H

#include "rtc_constants.h"

#include "rcrtc_constants.h"
#include "rcrtc_engine.h"
#include "rcrtc_room_setup.h"

#include <QWidget>

namespace Ui {
class RtcVideoRender;
}

class RtcVideoRender : public QWidget
{
    Q_OBJECT

public:
    explicit RtcVideoRender(QWidget *parent = nullptr);
    ~RtcVideoRender();
    void SetStreamInfo(rcrtc::RCRTCEngine* engine, const QString& user_id, const QString& tag, RemoteStreamType type);
    void AttachViewRender();
    void DetachViewRender();
    void NotifySubscribedStatus(bool is_subscribed);

private:
    Ui::RtcVideoRender *ui;
    QString user_id_;
    QString stream_tag_;
    rcrtc::RCRTCEngine* rcrtc_engine_;
    rcrtc::IRCRTCView* view_render_;
    RemoteStreamType stream_type_;
};

#endif // RTC_VIDEO_RENDER_H
