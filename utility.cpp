#include "utility.h"

rcrtc::RCRTCVideoResolution ConvertToVideoResolution(const QString& source) {
  rcrtc::RCRTCVideoResolution resolution;
  if ("RESOLUTION_172_144" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_144_176;
  } else if ("RESOLUTION_256_144" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_144_256;
  } else if ("RESOLUTION_180_180" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_180_180;
  } else if ("RESOLUTION_240_180" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_180_240;
  } else if ("RESOLUTION_320_180" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_180_320;
  } else if ("RESOLUTION_240_240" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_240_240;
  } else if ("RESOLUTION_320_240" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_240_320;
  } else if ("RESOLUTION_360_360" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_360_360;
  } else if ("RESOLUTION_480_360" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_360_480;
  } else if ("RESOLUTION_640_360" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_360_640;
  } else if ("RESOLUTION_480_480" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_480_480;
  } else if ("RESOLUTION_640_480" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_480_640;
  } else if ("RESOLUTION_848_480" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_480_848;
  } else if ("RESOLUTION_720_480" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_480_720;
  } else if ("RESOLUTION_960_720" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_720_960;
  } else if ("RESOLUTION_1280_720" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_720_1280;
  } else if ("RESOLUTION_1920_1080" == source) {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_1080_1920;
  } else {
    resolution = rcrtc::RCRTCVideoResolution::RESOLUTION_480_640;
  }
  return resolution;
}
QString ConvertToQString(const rcrtc::RCRTCVideoResolution& source) {
  QString resolution;
  if (rcrtc::RCRTCVideoResolution::RESOLUTION_144_176 == source) {
    resolution = "RESOLUTION_172_144";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_144_256 == source) {
    resolution = "RESOLUTION_256_144";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_180_180 == source) {
    resolution = "RESOLUTION_180_180";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_180_240 == source) {
    resolution = "RESOLUTION_240_180";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_180_320 == source) {
    resolution = "RESOLUTION_320_180";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_240_240 == source) {
    resolution = " RESOLUTION_240_240";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_240_320 == source) {
    resolution = "RESOLUTION_320_240";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_360_360 == source) {
    resolution = "RESOLUTION_360_360";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_360_480 == source) {
    resolution = "RESOLUTION_480_360";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_360_640 == source) {
    resolution = "RESOLUTION_640_360";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_480_480 == source) {
    resolution = "RESOLUTION_480_480";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_480_640 == source) {
    resolution = "RESOLUTION_640_480";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_480_848 == source) {
    resolution = "RESOLUTION_848_480";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_480_720 == source) {
    resolution = "RESOLUTION_720_480";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_720_960 == source) {
    resolution = "RESOLUTION_960_720";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_720_1280 == source) {
    resolution = "RESOLUTION_720_1280";
  } else if (rcrtc::RCRTCVideoResolution::RESOLUTION_1080_1920 == source) {
    resolution = "RESOLUTION_1920_1080";
  } else {
    resolution = "RESOLUTION_640_480";
  }
  return resolution;
}

rcrtc::RCRTCVideoFps ConvertToVideoFps(const QString& source) {
  rcrtc::RCRTCVideoFps fps;
  if ("FPS_10" == source) {
    fps = rcrtc::RCRTCVideoFps::FPS_10;
  } else if ("FPS_15" == source) {
    fps = rcrtc::RCRTCVideoFps::FPS_15;
  } else if ("FPS_24" == source) {
    fps = rcrtc::RCRTCVideoFps::FPS_24;
  } else if ("FPS_30" == source) {
    fps = rcrtc::RCRTCVideoFps::FPS_30;
  } else {
    fps = rcrtc::RCRTCVideoFps::FPS_24;
  }
  return fps;
}
QString ConvertToQString(const rcrtc::RCRTCVideoFps& source) {
  QString fps;
  if (rcrtc::RCRTCVideoFps::FPS_10 == source) {
    fps = "FPS_10";
  } else if (rcrtc::RCRTCVideoFps::FPS_15 == source) {
    fps = "FPS_15";
  } else if (rcrtc::RCRTCVideoFps::FPS_24 == source) {
    fps = "FPS_24";
  } else if (rcrtc::RCRTCVideoFps::FPS_30 == source) {
    fps = "FPS_30";
  } else {
    fps = "FPS_10";
  }
  return fps;
}

QString ConvertToQString(const rcrtc::RCRTCAudioQuality& source) {
  QString quality;
  if (rcrtc::RCRTCAudioQuality::SPEECH == source) {
    quality = "SPEECH";
  } else if (rcrtc::RCRTCAudioQuality::MUSIC == source) {
    quality = "MUSIC";
  } else if (rcrtc::RCRTCAudioQuality::MUSIC_HIGH == source) {
    quality = "MUSIC_HIGH";
  } else {
    quality = "SPEECH";
  }
  return quality;
}
rcrtc::RCRTCAudioQuality ConvertToAudioQuality(const QString& source) {
  rcrtc::RCRTCAudioQuality quality;
  if ("SPEECH" == source) {
    quality = rcrtc::RCRTCAudioQuality::SPEECH;
  } else if ("MUSIC" == source) {
    quality = rcrtc::RCRTCAudioQuality::MUSIC;
  } else if ("MUSIC_HIGH" == source) {
    quality = rcrtc::RCRTCAudioQuality::MUSIC_HIGH;
  } else {
    quality = rcrtc::RCRTCAudioQuality::SPEECH;
  }
  return quality;
}

QString ConvertToQString(const rcrtc::RCRTCAudioScenario& source) {
  QString scenario;
  if (rcrtc::RCRTCAudioScenario::DEFAULT == source) {
    scenario = "DEFAULT";
  } else if (rcrtc::RCRTCAudioScenario::MUSIC_CHATROOM == source) {
    scenario = "MUSIC_CHATROOM";
  } else if (rcrtc::RCRTCAudioScenario::MUSIC_CLASSROOM == source) {
    scenario = "MUSIC_CLASSROOM";
  } else {
    scenario = "DEFAULT";
  }
  return scenario;
}
rcrtc::RCRTCAudioScenario ConvertToAudioScenario(const QString& source) {
  rcrtc::RCRTCAudioScenario scenario;
  if ("DEFAULT" == source) {
    scenario = rcrtc::RCRTCAudioScenario::DEFAULT;
  } else if ("MUSIC_CHATROOM" == source) {
    scenario = rcrtc::RCRTCAudioScenario::MUSIC_CHATROOM;
  } else if ("MUSIC_CLASSROOM" == source) {
    scenario = rcrtc::RCRTCAudioScenario::MUSIC_CLASSROOM;
  } else {
    scenario = rcrtc::RCRTCAudioScenario::DEFAULT;
  }
  return scenario;
}

QString ConvertToQString(const rcrtc::RCRTCAudioMixingMode& source) {
  QString mode;
  if (rcrtc::RCRTCAudioMixingMode::NONE == source) {
    mode = "NONE";
  } else if (rcrtc::RCRTCAudioMixingMode::MIX == source) {
    mode = "MIX";
  } else if (rcrtc::RCRTCAudioMixingMode::REPLACE == source) {
    mode = "REPLACE";
  } else {
    mode = "NONE";
  }
  return mode;
}
rcrtc::RCRTCAudioMixingMode ConvertToAudioMixingMode(const QString& source) {
  rcrtc::RCRTCAudioMixingMode mode;
  if ("NONE" == source) {
    mode = rcrtc::RCRTCAudioMixingMode::NONE;
  } else if ("MIX" == source) {
    mode = rcrtc::RCRTCAudioMixingMode::MIX;
  } else if ("REPLACE" == source) {
    mode = rcrtc::RCRTCAudioMixingMode::REPLACE;
  } else {
    mode = rcrtc::RCRTCAudioMixingMode::NONE;
  }
  return mode;
}

QString ConvertToQString(const rcrtc::RCRTCMediaType& source) {
  QString mode;
  if (rcrtc::RCRTCMediaType::AUDIO == source) {
    mode = "AUDIO";
  } else if (rcrtc::RCRTCMediaType::VIDEO == source) {
    mode = "VIDEO";
  } else if (rcrtc::RCRTCMediaType::AUDIO_VIDEO == source) {
    mode = "AUDIO_VIDEO";
  } else {
    mode = "AUDIO_VIDEO";
  }
  return mode;
}
rcrtc::RCRTCMediaType ConvertToMediaType(const QString& source) {
  rcrtc::RCRTCMediaType media_type;
  if ("AUDIO" == source) {
    media_type = rcrtc::RCRTCMediaType::AUDIO;
  } else if ("VIDEO" == source) {
    media_type = rcrtc::RCRTCMediaType::VIDEO;
  } else if ("AUDIO_VIDEO" == source) {
    media_type = rcrtc::RCRTCMediaType::AUDIO_VIDEO;
  } else {
    media_type = rcrtc::RCRTCMediaType::AUDIO_VIDEO;
  }
  return media_type;
}

QString ConvertToQString(const rcrtc::RCRTCAudioCodecType& source) {
  QString mode;
  if (rcrtc::RCRTCAudioCodecType::PCMU == source) {
    mode = "PCMU";
  } else if (rcrtc::RCRTCAudioCodecType::OPUS == source) {
    mode = "OPUS";
  }
  return mode;
}
rcrtc::RCRTCAudioCodecType ConvertToAudioCodecType(const QString& source) {
  rcrtc::RCRTCAudioCodecType audio_codec;
  if ("PCMU" == source) {
    audio_codec = rcrtc::RCRTCAudioCodecType::PCMU;
  } else {
    audio_codec = rcrtc::RCRTCAudioCodecType::OPUS;
  }
  return audio_codec;
}

QString ConvertToQString(const rcrtc::RCRTCNetworkType& type) {
  if (rcrtc::RCRTCNetworkType::UNKNOWN == type) {
    return "UNKNOWN";
  } else if (rcrtc::RCRTCNetworkType::WIFI == type) {
    return "WIFI";
  } else if (rcrtc::RCRTCNetworkType::MOBILE == type) {
    return "MOBILE";
  }
  return "UNKNOWN";
}
rcrtc::RCRTCNetworkType ConvertToNetworkType(const QString& source) {
  if ("UNKNOWN" == source) {
    return rcrtc::RCRTCNetworkType::UNKNOWN;
  } else if ("WIFI" == source) {
    return rcrtc::RCRTCNetworkType::WIFI;
  } else if ("MOBILE" == source) {
    return rcrtc::RCRTCNetworkType::MOBILE;
  }
  return rcrtc::RCRTCNetworkType::UNKNOWN;
}

QString ConvertToQString(const rcrtc::RCRTCAudioCodec& type) {
  if (rcrtc::RCRTCAudioCodec::PCMU == type) {
    return "PCMU";
  } else if (rcrtc::RCRTCAudioCodec::OPUS == type) {
    return "OPUS";
  }
  return "UNKNOWN";
}
rcrtc::RCRTCAudioCodec ConvertToAudioCodec(const QString& source) {
  if ("PCMU" == source) {
    return rcrtc::RCRTCAudioCodec::PCMU;
  } else if ("OPUS" == source) {
    return rcrtc::RCRTCAudioCodec::OPUS;
  }
  return rcrtc::RCRTCAudioCodec::PCMU;
}

QString ConvertToQString(const rcrtc::RCRTCVideoCodecType& type) {
  if (rcrtc::RCRTCVideoCodecType::H264 == type) {
    return "H264";
  }
  return "UNKNOWN";
}
rcrtc::RCRTCVideoCodecType ConvertToVideoCodecType(const QString& source) {
  if ("H264" == source) {
    return rcrtc::RCRTCVideoCodecType::H264;
  }
  return rcrtc::RCRTCVideoCodecType::H264;
}

QString ConvertToQString(const rcrtc::RCRTCLiveMixLayoutMode& type) {
  if (rcrtc::RCRTCLiveMixLayoutMode::CUSTOM == type) {
    return "CUSTOM";
  } else if (rcrtc::RCRTCLiveMixLayoutMode::SUSPENSION == type) {
    return "SUSPENSION";
  } else if (rcrtc::RCRTCLiveMixLayoutMode::ADAPTIVE == type) {
    return "ADAPTIVE";
  } else {
    return "CUSTOM";
  }
}
rcrtc::RCRTCLiveMixLayoutMode ConvertToLiveMixLayoutMode(
    const QString& source) {
  if ("CUSTOM" == source) {
    return rcrtc::RCRTCLiveMixLayoutMode::CUSTOM;
  } else if ("SUSPENSION" == source) {
    return rcrtc::RCRTCLiveMixLayoutMode::SUSPENSION;
  } else if ("ADAPTIVE" == source) {
    return rcrtc::RCRTCLiveMixLayoutMode::ADAPTIVE;
  } else {
    return rcrtc::RCRTCLiveMixLayoutMode::CUSTOM;
  }
}
QString ConvertToQString(const rcrtc::RCRTCLiveMixRenderMode& type) {
  if (rcrtc::RCRTCLiveMixRenderMode::CROP == type) {
    return "CROP";
  } else if (rcrtc::RCRTCLiveMixRenderMode::WHOLE == type) {
    return "WHOLE";
  } else {
    return "CROP";
  }
}
rcrtc::RCRTCLiveMixRenderMode ConvertToLiveMixRenderMode(
    const QString& source) {
  if ("CROP" == source) {
    return rcrtc::RCRTCLiveMixRenderMode::CROP;
  } else if ("WHOLE" == source) {
    return rcrtc::RCRTCLiveMixRenderMode::WHOLE;
  } else {
    return rcrtc::RCRTCLiveMixRenderMode::CROP;
  }
}

QString ConvertToQString(const std::string& str) {
  return QString::fromUtf8(
      QByteArray::fromRawData(str.c_str(), (int)str.size()));
}
std::string ConvertTostdString(const QString& qs) {
  return qs.toUtf8().constData();
}
