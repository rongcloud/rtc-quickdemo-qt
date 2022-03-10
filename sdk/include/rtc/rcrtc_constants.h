/**
 * Copyright © 2022, RongCloud. All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RTCLIB_API_RCRTC_CONSTANTS_H
#define RTCLIB_API_RCRTC_CONSTANTS_H

#if defined(_WIN32)
#include <Windows.h>
#endif

#include <cstdint>
#include <string>

namespace rcrtc {

#if !defined(_WIN32)
typedef void* HANDLE;
#endif

/**
 * 媒体类型
 */
enum class RCRTCMediaType : int32_t {
  AUDIO = 0,
  VIDEO = 1,
  AUDIO_VIDEO = 2,
};

/**
 * 角色类型
 */
enum class RCRTCRole : int32_t {
  MEETING_MEMBER = 0,
  LIVE_BROADCASTER = 1,
  LIVE_AUDIENCE = 2,
};

/**
 * 加入房间类型
 */
enum class RCRTCJoinType : int32_t {
  /*!
   * 允许当前设备加入房间，服务端将同用户其他设备踢出房间
   */
  KICK_OTHER_DEVICE = 0,
  /*!
   * 同用户其他设备已进入房间，禁止当前设备加入房间
   */
  REFUSE_CURRENT_DEVICE = 1,
  /*!
   * 允许用户多个设备进入房间，暂时不支持
   */
  COEXIST = 2,  // extension
};

/**
 * 视频旋转角度
 */
enum class RCRTCCameraCaptureOrientation : int32_t {
  PORTRAIT = 0,
  LANDSCAPE_LEFT = 90,
  PORTRAIT_UPSIDE_DOWN = 180,
  LANDSCAPE_RIGHT = 270,
};

enum class RCRTCAudioQuality : int32_t {
  SPEECH = 32,
  MUSIC = 64,
  MUSIC_HIGH = 128,
};

enum class RCRTCAudioScenario : int32_t {
  DEFAULT = 0,
  MUSIC_CHATROOM = 1,
  MUSIC_CLASSROOM = 2,
};

enum class RCRTCVideoFps : int32_t {
  FPS_5 = 5,
  FPS_8 = 8,
  FPS_10 = 10,
  FPS_15 = 15,
  FPS_24 = 24,
  FPS_30 = 30,
};

enum class RCRTCVideoResolution : int32_t {
  RESOLUTION_144_176 = 1,
  RESOLUTION_144_256 = 2,
  RESOLUTION_180_180 = 3,
  RESOLUTION_180_240 = 4,
  RESOLUTION_180_320 = 5,
  RESOLUTION_240_240 = 6,
  RESOLUTION_240_320 = 7,
  RESOLUTION_360_360 = 8,
  RESOLUTION_360_480 = 9,
  RESOLUTION_360_640 = 10,
  RESOLUTION_480_480 = 11,
  RESOLUTION_480_640 = 12,
  RESOLUTION_480_848 = 13,
  RESOLUTION_480_720 = 14,
  RESOLUTION_720_960 = 15,
  RESOLUTION_720_1280 = 16,
  RESOLUTION_1080_1920 = 17,
};

enum class RCRTCViewFitType {
  FIT = 0,  // 图像等比缩放后，不裁剪，宽和高有一个和窗口一样，
            //另外一个比窗口小，然后在窗口居中显示
  FILL = 1,   // 图像拉伸后填充整个窗口，不保证原有比例
  COVER = 2,  // 图像等比缩放后，宽和高有一个和窗口一样，
              // 另外一个比窗口大，进行裁剪，然后填充整个窗口显示
  CENTER = 3,  // 原始图像的宽和高都比窗口小，则图像在窗口居中显示
};

/**
 * 视频存储格式
 */
enum class RCRTCVideoFormat : int32_t {
  YUV420P = 0,
};

/**
 * 音频存储格式
 */
enum class RCRTCAudioSampleFormat : int32_t {
  AUDIO_FMT_NONE = -1,
  AUDIO_FMT_U8,   ///< unsigned 8 bits
  AUDIO_FMT_S16,  ///< signed 16 bits
  AUDIO_FMT_S32,  ///< signed 32 bits
  AUDIO_FMT_FLT,  ///< float
  AUDIO_FMT_DBL,  ///< double

  AUDIO_FMT_U8P,   ///< unsigned 8 bits, planar
  AUDIO_FMT_S16P,  ///< signed 16 bits, planar
  AUDIO_FMT_S32P,  ///< signed 32 bits, planar
  AUDIO_FMT_FLTP,  ///< float, planar
  AUDIO_FMT_DBLP,  ///< double, planar
  AUDIO_FMT_S64,   ///< signed 64 bits
  AUDIO_FMT_S64P,  ///< signed 64 bits, planar
  AUDIO_FMT_NB     ///< Number of sample formats. DO NOT USE if linking
                   ///< dynamically
};

enum class RCRTCErrorCode : int32_t {
  // 通用错误码
  RCRTC_ERROR = -1,   // 错误
  RCRTC_SUCCESS = 0,  // 成功

  RCRTC_ENGINE_NOT_INIT = 1000,  // 媒体对象未初始化
  RCRTC_CLIENT_NOT_INIT = 1001,  // 信令对象未初始化
  RCRTC_NOT_CONNECTED = 1002,    // 未连接服务
  RCRTC_NOT_IN_ROOM = 1003,      // 未在房间内
  RCRTC_ENTERING_ROOM = 1004,    // 正在进入房间
  RCRTC_ALREADY_IN_ROOM = 1005,  // 已经在房间内
  RCRTC_LEAVEING_ROOM = 1006,    // 正在退出房间
  RCRTC_ROLE_SWITCHING = 1007,   // 正在切换角色

  RCRTC_PARAM_ERROR = 1100,  // 参数错误

  // 设备相关
  RCRTC_DEVICE_INVALID_PARAM = 1200,    // 设备参数无效
  RCRTC_DEVICE_INVALID_INDEX = 1201,    // 无效的设备索引
  RCRTC_DEVICE_NO_DEFAULT = 1202,       // 未指定默认设备
  RCRTC_DEVICE_RESOURCES_EMPTY = 1203,  // 设备资源列表为空

  // 引擎内部错误
  RCRTC_ENGINE_INTERNAL_ERROR = 1300,            // 引擎内部错误
  RCRTC_ENGINE_STREAM_NOT_EXIST = 1301,          // 不存在流信息
  RCRTC_ENGINE_STREAM_ALREADY_EXIST = 1302,      // 已经存在流信息
  RCRTC_ENGINE_CREATE_TRACK_ERROR = 1303,        // 创建track 失败
  RCRTC_ENGINE_ADD_TRACK_ERROR = 1304,           // 添加track失败
  RCRTC_ENGINE_CREATE_SOURCE_ERROR = 1305,       // 创建音视频源失败
  RCRTC_ENGINE_CREATE_OPENGL_ERROR = 1306,       // 创建OpenGL失败
  RCRTC_ENGINE_STREAM_TAG_DUPLICATE = 1307,      // tag 标签重复
  RCRTC_ENGINE_PUBLISH_NOT_EXIST_STREAM = 1308,  // 发布不存在的资源
  RCRTC_ENGINE_ROLE_NOT_IS_ANCHOR = 1309,  // 当前角色不是主播，没有相应权限

  /**
   * internal error 服务器内部错误
   */
  RCRTC_SIGNAL_INTERNAL_ERROR = 40002,

  // HTTP 服务器没有处理器	HTTP URI 不合法
  RCRTC_MEDIA_HTTP_URI_INVALID = 41002,
  // HTTP 请求参数错误	HTTP 请求参数不合法
  RCRTC_MEDIA_HTTP_REQUEST_PARAM_ERROR = 41003,
  // HTTP 请求发送到服务器失败	HTTP 处理请求内容时出错
  RCRTC_MEDIA_HTTP_PROCESS_ERROR = 41004,
  // HTTP 接收响应长度错误	处理级联接收请求时出错
  RCRTC_MEDIA_HTTP_LENGTH_ERROR = 41005,
  // URI NOTFOUND
  RCRTC_MEDIA_URI_NOTFOUND = 41006,
  // 身份验证主机错误
  RCRTC_MEDIA_AUTHENTICATION_HOST_ERROR = 41007,
  // 内部错误
  RCRTC_MEDIA_INTERNAL_ERROR = 41008,
  // 应用密钥无效
  RCRTC_MEDIA_APPLICATION_KEY_INVALID = 41009,
  // 缺少标头应用密钥或令牌 RO ROOMID 或客户端类型	认证头缺失
  RCRTC_MEDIA_AUTHENTICATION_ERROR = 42001,
  // 令牌无效
  RCRTC_MEDIA_TOKEN_INVALID = 42002,
  // 令牌不在房间内
  RCRTC_MEDIA_TOKEN_NOT_IN_ROOM = 42003,
  // LIVEURL 缺失
  RCRTC_MEDIA_LIVEURL_MISSING = 42004,
  // 令牌中的会话无效	加入房间模式：SESSIONID 缺失
  RCRTC_MEDIA_SESSIONID_MISSING = 42005,
  // JSON 格式错误
  RCRTC_MEDIA_JSON_PARSING_ERROR = 43001,
  // SDP 解析错误
  RCRTC_MEDIA_SDP_PARSING_ERROR = 43002,
  // 构建订阅列表出错
  RCRTC_MEDIA_RESOURCE_LIST_ERROR = 44001,
  // 用户不在服务器中
  RCRTC_MEDIA_USER_NOT_EXIST = 45001,
  // 用户身份解码失败
  RCRTC_MEDIA_IDENTITY_DECODING_ERROR = 45002,
  // 执行订阅错误
  RCRTC_MEDIA_SUBSCRIBE_ERROR = 45003,
  // 执行级联订阅错误
  RCRTC_MEDIA_CASCADE_SUBSCRIBE_ERROR = 45004,
  // 服务器推流出现错误
  RCRTC_MEDIA_PUBLISH_ERROR = 45005,
  // MCU发布视频失败
  RCRTC_MEDIA_MCU_PUBLISH_ERROR = 45006,
  // 实时订阅失败
  RCRTC_MEDIA_LIVE_SUBSCRIBE__ERROR = 45007,
  // 解析LIVE URL失败
  RCRTC_MEDIA_LIVE_URLPARSING_ERROR = 45008,
  // 会话已过期
  RCRTC_MEDIA_SESSION_EXPIRED = 45010,
  // LIVEURL 已过期
  RCRTC_MEDIA_LIVEURL_EXPIRED = 45011,
  // 解析推送配置信息出错
  RCRTC_MEDIA_PUBLISH_CONFIG_ERROR = 45013,
  // MCU NO PUBLISH	没有该直播
  RCRTC_MEDIA_MCU_NO_PUBLISH = 45014,
  // 不支持的用户被分配到混淆媒体服务器
  // 该服务器是混淆服务器，但是客户端不支持混淆
  RCRTC_MEDIA_INVALID_LIVE_STREAM_USER = 45015,
  // CDN 缓存不存在
  RCRTC_MEDIA_CDN_CACHE_NOT_EXIST = 45016,
  // 未知异常
  RCRTC_MEDIA_UNKONW_ERROR = 45099,

  /**
   * 用户被踢下线
   * 当前用户在其他设备上登录，此设备被踢下线
   * SDK 不会重连
   */
  RCRTC_CONNECTION_KICKED = 31010,
  /**
   * 初始化失败，信令服务（IM Server）未连接
   */
  RCRTC_CODE_SIGNAL_SERVER_NOT_CONNECT = 50000,
  /**
   * 参数错误
   */
  RCRTC_CODE_PARAMETER_ERROR = 50001,
  /**
   * 加入相同房间错误，表示用户在客户端重复加入相同的房间
   */
  RCRTC_CODE_JOIN_SAME_ROOM = 50002,
  /**
   * 不在房间中
   */
  RCRTC_CODE_NOT_IN_ROOM = 50003,
  /**
   * 请检查是否开通音视频服务
   */
  RCRTC_CODE_ENGINE_ERROR = 50004,
  /**
   *  RTC token为空，请查看是否还在房间内或者房间是否销毁
   */
  RCRTC_CODE_TOKEN_IS_NULL = 50006,
  /**
   * RTC 加入直播房间超时
   */
  RCRTC_JOIN_CHAT_ROOM_TIMEOUT = 50008,
  /**
   * HTTP 请求超时
   */
  RCRTC_CODE_HTTP_TIMEOUT_ERROR = 50010,
  /**
   * HTTP 响应错误（含 500，404，405 等错误）
   */
  RCRTC_CODE_HTTP_RESPONSE_ERROR = 50011,
  /**
   * HTTP 请求错误（含网络不可达，请求未能为能正常发出）
   */
  RCRTC_CODE_HTTP_REQUEST_ERROR = 50012,
  /**
   * 发布重复资源
   */
  RCRTC_CODE_PUBLISH_DUPLICATE_RESOURCES = 50020,
  /**
   * 初步会话协商错误，没有消息的音视频参数
   */
  RCRTC_CODE_SESSION_DEGOTIATE_OFFER_ERROR = 50021,
  /**
   * 会话协商错误，协商数据不匹配或者其他问题
   */
  RCRTC_CODE_SESSION_DEGOTIATE_SET_REMOTE_ERROR = 50022,
  /**
   * 发布的流的个数已经到达上限
   */
  RCRTC_CODE_PUBLISH_STREAM_HAS_REACHED_MAX_COUNT = 50023,
  /**
   * 取消发布不存在的资源
   */
  RCRTC_CODE_UNPUBLISH_NOT_EXIST_STREAM = 50024,
  /**
   * 订阅不存在的音视频资源
   */
  RCRTC_CODE_SUBSCRIBE_NOT_EXIST_RESOURCES = 50030,
  /**
   * 资源重复订阅
   */
  RCRTC_CODE_SUBSCRIBE_DUPLICATE_RESOURCES = 50031,
  /**
   * 取消订阅不存在的音视频资源
   */
  RCRTC_CODE_UNSUBSCRIBE_NOT_EXIST_RESOURCE = 50032,
  /**
   * SDK 内部业务逻辑错误码
   */
  RCRTC_CODE_SDK_INTERNAL_ERROR = 50071,
  /**
   * cdn 地址配置数量到达上限（最大为10个）
   */
  RCRTC_CODE_CDN_COUNT_REACH_LIMIT = 50080,
};

enum class RCRTCAudioCodec {
  PCMU = 0,
  OPUS = 1,
};

enum class RCRTCAudioCodecType {
  PCMU = 0,
  OPUS = 111,
};

enum class RCRTCAudioMixingMode {
  NONE = 0,
  MIX,
  REPLACE,
};

enum class RCRTCLiveMixLayoutMode {
  CUSTOM = 0,
  SUSPENSION,
  ADAPTIVE,
};

enum class RCRTCLiveMixRenderMode {
  CROP = 0,
  WHOLE,
};

enum class RCRTCNetworkType {
  UNKNOWN = 0,
  WIFI = 1,
  MOBILE = 2,
};

enum class RCRTCVideoCodecType {
  H264 = 0,
};

enum class RCRTCVideoCaptureType {
  UNKNOWN = 0,
  YUV_I420,
  TINY,
  YUV_FILE,
  CAMERA,
  CAPTUREDESKTOP,
  CAPTUREWINDOW,
};

struct RCRTCNetworkStats {
  RCRTCNetworkType type;
  std::string ip;
  int32_t sendBitrate;
  int32_t receiveBitrate;
  int32_t rtt;

  RCRTCNetworkStats() {
    type = RCRTCNetworkType::UNKNOWN;
    ip = "";
    sendBitrate = 0;
    receiveBitrate = 0;
    rtt = 0;
  }
};

struct RCRTCAudioStats {
  RCRTCAudioCodec codec;
  int32_t bitrate;
  int32_t volume;
  double packageLostRate;
  int32_t rtt;

  RCRTCAudioStats() {
    codec = RCRTCAudioCodec::OPUS;
    bitrate = 0;
    volume = 0;
    packageLostRate = 0.0;
    rtt = 0;
  }
};

struct RCRTCVideoStats {
  RCRTCVideoCodecType codec;
  int32_t bitrate;
  int32_t fps;
  int32_t width;
  int32_t height;
  int32_t rtt;
  bool tiny;
  double packageLostRate;
  RCRTCVideoStats() {
    codec = RCRTCVideoCodecType::H264;
    bitrate = 0;
    fps = 0;
    width = 0;
    height = 0;
    rtt = 0;
    tiny = false;
    packageLostRate = 0.0;
  }
};

struct RCRTCCustomLayout {
  std::string userId;
  std::string tag;
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
  RCRTCCustomLayout() {
    userId = "";
    tag = "";
    x = 0;
    y = 0;
    width = 0;
    height = 0;
  }
};

struct RCRTCSubscribeInfo {
  std::string user_id;
  RCRTCMediaType media_type;
  bool is_tiny;
  RCRTCSubscribeInfo()
      : media_type(RCRTCMediaType::AUDIO_VIDEO), is_tiny(false) {}
  RCRTCSubscribeInfo(const std::string& user, RCRTCMediaType type, bool tiny)
      : user_id(user), media_type(type), is_tiny(tiny) {}
};

struct RCRTCVideoCaptureInfo {
  RCRTCVideoCaptureType capture_type;
  int32_t x_offset;
  int32_t y_offset;
  int32_t width;
  int32_t height;
  int64_t device_index;
  bool is_capture_mouse;
  std::string device_url;
  RCRTCVideoCaptureInfo()
      : capture_type(RCRTCVideoCaptureType::UNKNOWN),
        x_offset(0),
        y_offset(0),
        width(0),
        height(0),
        device_index(0),
        is_capture_mouse(false) {}
};

struct RCRTCAudioFrame {
  char* data;
  uint32_t data_size;
  uint32_t sampleRate;
  uint32_t channel;
  uint32_t sample_bytes;
  uint64_t timestamp;

  RCRTCAudioFrame()
      : data(nullptr),
        data_size(0),
        sampleRate(48000),
        channel(1),
        sample_bytes(2),
        timestamp(0) {}
};

struct RCRTCVideoFrame {
  char* data;
  uint32_t data_size;
  uint32_t width;
  uint32_t height;
  uint32_t stride_y;
  uint32_t stride_u;
  uint32_t stride_v;
  uint64_t timestamp;

  RCRTCVideoFrame()
      : data(nullptr),
        data_size(0),
        width(640),
        height(480),
        stride_y(640),
        stride_u(320),
        stride_v(320),
        timestamp(0) {}
};

struct RCRTCStreamKey {
  std::string user_id;
  std::string tag;

  RCRTCStreamKey() = default;
  RCRTCStreamKey(const std::string& _user_id, const std::string& _tag)
      : user_id(_user_id), tag(_tag) {}

  bool operator<(const RCRTCStreamKey& o) const {
    if (user_id != o.user_id) {
      return user_id < o.user_id;
    }
    if (tag != o.tag) {
      return tag < o.tag;
    }
    return false;
  }

  bool operator==(const RCRTCStreamKey& o) const {
    if (user_id != o.user_id) {
      return false;
    }
    if (tag != o.tag) {
      return false;
    }
    return true;
  }

  bool operator!=(const RCRTCStreamKey& o) const { return !(*this == o); }
};

struct RCRTCUserJoinedRoom {
  std::string room_id;
  std::string device_id;
  int64_t join_time;

  RCRTCUserJoinedRoom() = default;
  RCRTCUserJoinedRoom(const std::string& roomId,
                      const std::string& deviceId,
                      int64_t joinTime)
      : room_id(roomId), device_id(deviceId), join_time(joinTime) {}
};
}  // namespace rcrtc
#endif
