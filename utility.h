#ifndef UTILITY_H
#define UTILITY_H
#include <QString>

#include "rcrtc_engine.h"



QString ConvertToQString(const rcrtc::RCRTCVideoFps& source);
rcrtc::RCRTCVideoResolution ConvertToVideoResolution(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCVideoResolution& source);
rcrtc::RCRTCVideoFps ConvertToVideoFps(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCAudioQuality& source);
rcrtc::RCRTCAudioQuality ConvertToAudioQuality(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCAudioScenario& source);
rcrtc::RCRTCAudioScenario ConvertToAudioScenario(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCAudioMixingMode& source);
rcrtc::RCRTCAudioMixingMode ConvertToAudioMixingMode(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCMediaType& source);
rcrtc::RCRTCMediaType ConvertToMediaType(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCAudioCodecType& source);
rcrtc::RCRTCAudioCodecType ConvertToAudioCodecType(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCNetworkType& type);
rcrtc::RCRTCNetworkType ConvertToNetworkType(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCAudioCodec& type);
rcrtc::RCRTCAudioCodec ConvertToAudioCodec(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCVideoCodecType& type);
rcrtc::RCRTCVideoCodecType ConvertToVideoCodecType(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCLiveMixLayoutMode& type);
rcrtc::RCRTCLiveMixLayoutMode ConvertToLiveMixLayoutMode(const QString& source);

QString ConvertToQString(const rcrtc::RCRTCLiveMixRenderMode& type);
rcrtc::RCRTCLiveMixRenderMode ConvertToLiveMixRenderMode(const QString& source);

QString ConvertToQString(const std::string& str);
std::string ConvertTostdString(const QString& qs);


#endif  // UTILITY_H
