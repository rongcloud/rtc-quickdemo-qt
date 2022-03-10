#ifndef RTC_CONSTANTS_H
#define RTC_CONSTANTS_H


#include "rcrtc_engine.h"
#include <QString>

struct RemoteMediaInfo {
    QString user_id_;
    QString stream_tag_;
    rcrtc::RCRTCMediaType media_type_;

    RemoteMediaInfo() = default;
    RemoteMediaInfo(const QString& user_id,
                    const QString& tag,
                    rcrtc::RCRTCMediaType type)
        : user_id_(user_id), stream_tag_(tag), media_type_(type) {}

    bool operator!=(const RemoteMediaInfo& o) const {
        if (user_id_ != o.user_id_) {
            return true;
        }
        if (stream_tag_ != o.stream_tag_) {
            return true;
        }
        if (media_type_ != o.media_type_) {
            return true;
        }
        return false;
    }

    bool operator<(const RemoteMediaInfo& o) const {
        if (user_id_ != o.user_id_) {
            return user_id_ <  o.user_id_;
        }
        if (stream_tag_ != o.stream_tag_) {
            return stream_tag_ < o.stream_tag_;
        }
        if (media_type_ != o.media_type_) {
            return media_type_ <  o.media_type_;
        }
        return false;
    }
    bool operator==(const RemoteMediaInfo& o) const { return !operator!=(o); }
};


typedef struct Stream_Key {
    QString user_id;
    QString tag;

    Stream_Key() = default;
    Stream_Key(const QString& _user_id, const QString& _tag)
        : user_id(_user_id), tag(_tag) {}

    bool operator!=(const Stream_Key& o) const {
        if (user_id != o.user_id) {
            return true;
        }
        if (tag != o.tag) {
            return true;
        }
        return false;
    }

    bool operator==(const Stream_Key& o) const { return !operator!=(o); }
} Stream_Key;

enum RemoteStreamType{
    STREAM_TYPE_DEFAULT =0,
    STREAM_TYPE_CUSTOM =1,
    STREAM_TYPE_LIVE =2,

};

#endif // RTC_CONSTANTS_H
