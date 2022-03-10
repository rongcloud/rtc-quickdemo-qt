#include "rtc_video_render.h"
#include "ui_rtc_video_render.h"

#include "utility.h"

RtcVideoRender::RtcVideoRender(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtcVideoRender),
    rcrtc_engine_(nullptr),
    view_render_(nullptr),
    stream_type_(STREAM_TYPE_DEFAULT)
{
    ui->setupUi(this);
    setFixedSize(300,300);
}

RtcVideoRender::~RtcVideoRender()
{
    delete ui;
}

void RtcVideoRender::SetStreamInfo(rcrtc::RCRTCEngine* engine, const QString& user_id, const QString& tag, RemoteStreamType type)
{
    user_id_ = user_id;
    stream_tag_ = tag;
    rcrtc_engine_ = engine;
    stream_type_ = type;

    ui->label_stream_tag->setText(stream_tag_);
    ui->label_user_id->setText(user_id_);
}

void RtcVideoRender::AttachViewRender()
{
    if(nullptr == rcrtc_engine_){
        return;
    }
    HANDLE viewId = (HANDLE)ui->widget_view_render->winId();
    view_render_ = rcrtc::IRCRTCView::create((HANDLE)viewId);
    view_render_->setMirror(false);
    view_render_->setFitType(rcrtc::RCRTCViewFitType::FIT);
    if(STREAM_TYPE_DEFAULT == stream_type_){
        rcrtc_engine_->setRemoteView(ConvertTostdString(user_id_), view_render_);
    } else if(STREAM_TYPE_CUSTOM == stream_type_){
        rcrtc_engine_->setRemoteCustomStreamView(ConvertTostdString(user_id_),ConvertTostdString(stream_tag_), view_render_);
    } else if(STREAM_TYPE_LIVE == stream_type_){
        rcrtc_engine_->setLiveMixView(view_render_);
    }
}

void RtcVideoRender::DetachViewRender()
{
    if(nullptr == rcrtc_engine_ || nullptr == view_render_){
        return;
    }
    if(STREAM_TYPE_DEFAULT == stream_type_){
        rcrtc_engine_->removeRemoteView(ConvertTostdString(user_id_));
    } else if(STREAM_TYPE_CUSTOM == stream_type_){
        rcrtc_engine_->removeRemoteCustomStreamView(ConvertTostdString(user_id_),ConvertTostdString(stream_tag_));
    } else if(STREAM_TYPE_LIVE == stream_type_){
        rcrtc_engine_->removeLiveMixView();
    }
    rcrtc::IRCRTCView::destroy(&view_render_);
}

void RtcVideoRender::NotifySubscribedStatus(bool is_subscribed)
{
    QString  style = "QWidget{background-color:black;};";
    if(is_subscribed){
        style = "QWidget{background-color: rgb(105, 105, 105);};";
    }
    ui->widget_view_render->setStyleSheet(style);
}
