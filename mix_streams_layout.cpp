/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */

 // clang-format off
#include "mix_streams_layout.h"
#include <libc_engine.h>
// clang-format on


namespace rc_mix_test {

	bool JsonTransform::FromJson(const nlohmann::json& json) {
		return false;
	}

	bool JsonTransform::FromJsonString(const std::string& json_str) {
		if (!json_str.empty())
		{
			try
			{
				nlohmann::json json = nlohmann::json::parse(json_str.c_str());
				return FromJson(json);
			}
			catch (const std::exception&)
			{
				return false;
			}
		}
		return false;
	}

	bool JsonTransform::ToJson(nlohmann::json* json) {
		return false;
	}

	bool JsonTransform::ToJsonString(std::string* json_str) {
		if (!json_str) {
			return false;
		}

		nlohmann::json json;
		if (ToJson(&json)) {
			*json_str = json.dump();
			return true;
		}
		return false;
	}

	bool JsonTransform::HasValue() const {
		return true;
	}

	/************************************MixStreamsBGPicture***************************************/

	MixStreamsBGPicture::MixStreamsBGPicture()
		: x_(0.0), y_(0.0), w_(1.0), h_(1.0) {}

	MixStreamsBGPicture::MixStreamsBGPicture(float x,
		float y,
		float w,
		float h,
		const std::string& uri)
		: x_(x), y_(y), w_(w), h_(h), uri_(uri) {}

	MixStreamsBGPicture::~MixStreamsBGPicture() {}

	bool MixStreamsBGPicture::operator==(const MixStreamsBGPicture& o) {
		if (x_ == o.x_ && y_ == o.y_ && w_ == o.w_ && h_ == o.h_ &&
			uri_.compare(o.uri_) == 0) {
			return true;
		}
		return false;
	}

	bool MixStreamsBGPicture::operator!=(const MixStreamsBGPicture& o) {
		return !(*this == o);
	}

	bool MixStreamsBGPicture::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("uri") != json.end()) {
				val = json["uri"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(uri_);
				}
			}

			if (json.find("x") != json.end()) {
				val = json["x"];
				if (!val.is_null() && val.is_number()) {
					x_ = val.get<float>();
				}
			}

			if (json.find("y") != json.end()) {
				val = json["y"];
				if (!val.is_null() && val.is_number()) {
					y_ = val.get<float>();
				}
			}

			if (json.find("w") != json.end()) {
				val = json["w"];
				if (!val.is_null() && val.is_number()) {
					w_ = val.get<float>();
				}
			}

			if (json.find("h") != json.end()) {
				val = json["h"];
				if (!val.is_null() && val.is_number()) {
					h_ = val.get<float>();
				}
			}
			return true;
		}

		return false;
	}

	bool MixStreamsBGPicture::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;
			if (!uri_.empty()) {
				json["uri"] = uri_;
			}
			if (x_ >= 0.0) {
				json["x"] = x_;
			}
			if (y_ >= 0.0) {
				json["y"] = y_;
			}
			if (w_ > 0.0) {
				json["w"] = w_;
			}
			if (h_ > 0.0) {
				json["h"] = h_;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsBGPicture::HasValue() const {
		if (x_ < 0.0 || x_ > 1.0) {
			return false;
		}
		if (y_ < 0.0 || y_ > 1.0) {
			return false;
		}
		if (w_ < 0.0 || w_ > 1.0) {
			return false;
		}
		if (h_ < 0.0 || h_ > 1.0) {
			return false;
		}
		if (uri_.empty()) {
			return false;
		}
		return true;
	}

	/************************************MixStreamsInputAudio***************************************/

	MixStreamsInputAudio::MixStreamsInputAudio() {}

	MixStreamsInputAudio::MixStreamsInputAudio(const std::string& user_id,
		const std::string& stream_id)
		: user_id_(user_id), stream_id_(stream_id) {}

	MixStreamsInputAudio::~MixStreamsInputAudio() {}

	bool MixStreamsInputAudio::operator==(const MixStreamsInputAudio& o) {
		if (user_id_.compare(o.user_id_) == 0 &&
			stream_id_.compare(o.stream_id_) == 0) {
			return true;
		}
		return false;
	}

	bool MixStreamsInputAudio::operator!=(const MixStreamsInputAudio& o) {
		return !(*this == o);
	}

	bool MixStreamsInputAudio::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("user_id") != json.end()) {
				val = json["user_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(user_id_);
				}
			}

			if (json.find("stream_id") != json.end()) {
				val = json["stream_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(stream_id_);
				}
			}
			return true;
		}

		return false;
	}

	bool MixStreamsInputAudio::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;
			if (!user_id_.empty()) {
				json["user_id"] = user_id_;
			}
			if (!stream_id_.empty()) {
				json["stream_id"] = stream_id_;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsInputAudio::HasValue() const {
		if (user_id_.empty() && stream_id_.empty()) {
			return true;
		}
		return false;
	}

	/************************************MixStreamsInputVideo***************************************/

	MixStreamsInputVideo::MixStreamsInputVideo()
		: x_(INVALID_VALUE), y_(INVALID_VALUE), width_(0), height_(0) {}

	MixStreamsInputVideo::MixStreamsInputVideo(int x,
		int y,
		int w,
		int h,
		const std::string& user_id,
		const std::string& stream_id)
		: x_(x),
		y_(y),
		width_(w),
		height_(h),
		user_id_(user_id),
		stream_id_(stream_id) {}

	MixStreamsInputVideo::MixStreamsInputVideo(const MixStreamsInputVideo& o) {
		*this = o;
	}

	MixStreamsInputVideo& MixStreamsInputVideo::operator=(
		const MixStreamsInputVideo& o) {
		x_ = o.x_;
		y_ = o.y_;
		width_ = o.width_;
		height_ = o.height_;
		user_id_ = o.user_id_;
		stream_id_ = o.stream_id_;
		return *this;
	}

	MixStreamsInputVideo::~MixStreamsInputVideo() {}

	bool MixStreamsInputVideo::operator==(const MixStreamsInputVideo& o) {
		if (x_ == o.x_ && y_ == o.y_ && width_ == o.width_ && height_ == o.height_ &&
			user_id_.compare(o.user_id_) == 0 &&
			stream_id_.compare(o.stream_id_) == 0) {
			return true;
		}
		return false;
	}

	bool MixStreamsInputVideo::operator!=(const MixStreamsInputVideo& o) {
		return !(*this == o);
	}

	bool MixStreamsInputVideo::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("x") != json.end()) {
				val = json["x"];
				if (!val.is_null() && val.is_number()) {
					x_ = val.get<int>();
				}
			}

			if (json.find("y") != json.end()) {
				val = json["y"];
				if (!val.is_null() && val.is_number()) {
					y_ = val.get<int>();
				}
			}

			if (json.find("width") != json.end()) {
				val = json["width"];
				if (!val.is_null() && val.is_number()) {
					width_ = val.get<int>();
				}
			}

			if (json.find("height") != json.end()) {
				val = json["height"];
				if (!val.is_null() && val.is_number()) {
					height_ = val.get<int>();
				}
			}

			if (json.find("user_id") != json.end()) {
				val = json["user_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(user_id_);
				}
			}

			if (json.find("stream_id") != json.end()) {
				val = json["stream_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(stream_id_);
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsInputVideo::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;
			if (x_ >= 0) {
				json["x"] = x_;
			}
			if (y_ >= 0) {
				json["y"] = y_;
			}
			if (width_ > 0) {
				json["width"] = width_;
			}
			if (height_ > 0) {
				json["height"] = height_;
			}
			if (!user_id_.empty()) {
				json["user_id"] = user_id_;
			}
			if (!stream_id_.empty()) {
				json["stream_id"] = stream_id_;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsInputVideo::HasValue() const {
		if (x_ < 0 && y_ < 0 && width_ <= 0 && height_ <= 0 && user_id_.empty() &&
			stream_id_.empty()) {
			return false;
		}
		return true;
	}

	/************************************MixStreamsInput***************************************/

	MixStreamsInput::MixStreamsInput() {}

	MixStreamsInput::MixStreamsInput(const MixStreamsInput& o) {
		*this = o;
	}

	MixStreamsInput& MixStreamsInput::operator=(const MixStreamsInput& o) {
		audios_.clear();
		auto ait = o.audios_.begin();
		while (ait != o.audios_.end()) {
			audios_.push_back(*ait);
			ait++;
		}

		videos_.clear();
		auto vit = o.videos_.begin();
		while (vit != o.videos_.end()) {
			videos_.push_back(*vit);
			vit++;
		}

		return *this;
	}

	MixStreamsInput::~MixStreamsInput() {}

	bool MixStreamsInput::operator==(const MixStreamsInput& o) {
		if (audios_.size() == o.audios_.size()) {
			auto it = audios_.begin();
			while (it != audios_.end()) {
				bool equ = false;
				auto oit = o.audios_.begin();
				while (oit != o.audios_.end()) {
					if (*it == *oit) {
						equ = true;
					}
					oit++;
				}
				if (!equ) {
					return false;
				}
				it++;
			}
		}
		else {
			return false;
		}

		if (videos_.size() == o.videos_.size()) {
			auto it = videos_.begin();
			while (it != videos_.end()) {
				bool equ = false;
				auto oit = o.videos_.begin();
				while (oit != o.videos_.end()) {
					if (*it == *oit) {
						equ = true;
					}
					oit++;
				}
				if (!equ) {
					return false;
				}
				it++;
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool MixStreamsInput::operator!=(const MixStreamsInput& o) {
		return !(*this == o);
	}

	bool MixStreamsInput::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("audio") != json.end()) {
				val = json["audio"];
				if (!val.is_null() && val.is_array()) {
					audios_.clear();
					auto it = val.begin();
					while (it != val.end()) {
						MixStreamsInputAudio audio;
						audio.FromJson(*it);
						audios_.push_back(audio);
						it++;
					}
				}
			}

			if (json.find("video") != json.end()) {
				val = json["video"];
				if (!val.is_null() && val.is_array()) {
					videos_.clear();
					auto it = val.begin();
					while (it != val.end()) {
						MixStreamsInputVideo video;
						video.FromJson(*it);
						videos_.push_back(video);
						it++;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsInput::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			auto it_a = audios_.begin();
			while (it_a != audios_.end()) {
				nlohmann::json a;
				if (it_a->ToJson(&a)) {
					json["audio"].push_back(a);
				}
				it_a++;
			}

			auto it_v = videos_.begin();
			while (it_v != videos_.end()) {
				nlohmann::json v;
				if (it_v->ToJson(&v)) {
					json["video"].push_back(v);
				}
				it_v++;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsInput::HasValue() const {
		if (audios_.empty() && videos_.empty()) {
			return false;
		}
		return true;
	}

	bool MixStreamsInput::AppendAudio(const nlohmann::json& json) {
		MixStreamsInputAudio audio;
		if (audio.FromJson(json))
		{
			audios_.push_back(audio);
			return true;
		}
		return false;
	}

	bool MixStreamsInput::AppendVideo(const nlohmann::json& json) {
		MixStreamsInputVideo video;
		if (video.FromJson(json))
		{
			videos_.push_back(video);
			return true;
		}
		return false;
	}


	/************************************MixStreamsOutputAudio***************************************/

	MixStreamsOutputAudio::MixStreamsOutputAudio() : bitrate_kbps_(0) {}

	MixStreamsOutputAudio::MixStreamsOutputAudio(int bitrate_kbps)
		: bitrate_kbps_(bitrate_kbps) {}

	MixStreamsOutputAudio::~MixStreamsOutputAudio() {}

	bool MixStreamsOutputAudio::operator==(const MixStreamsOutputAudio& o) {
		if (bitrate_kbps_ == o.bitrate_kbps_) {
			return true;
		}
		return false;
	}

	bool MixStreamsOutputAudio::operator!=(const MixStreamsOutputAudio& o) {
		return !(*this == o);
	}

	bool MixStreamsOutputAudio::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			if (json.find("bitrate") != json.end()) {
				nlohmann::json val;
				val = json["bitrate"];
				if (!val.is_null() && val.is_number()) {
					bitrate_kbps_ = val.get<int>();
				}
				return true;
			}
		}

		return false;
	}

	bool MixStreamsOutputAudio::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			if (bitrate_kbps_ > 0) {
				nlohmann::json json;
				json["bitrate"] = bitrate_kbps_;
				*pjson = json;
				return true;
			}
		}
		return false;
	}

	bool MixStreamsOutputAudio::HasValue() const {
		if (bitrate_kbps_ <= 0) {
			return false;
		}
		return true;
	}

	/************************************MixStreamsOutputVideoConfig***************************************/

	MixStreamsOutputVideoConfig::MixStreamsOutputVideoConfig()
		: width_(0), height_(0), fps_(0), bitrate_kbps_(0) {}

	MixStreamsOutputVideoConfig::MixStreamsOutputVideoConfig(int w,
		int h,
		int fps,
		int b)
		: width_(w), height_(h), fps_(fps), bitrate_kbps_(b) {}

	MixStreamsOutputVideoConfig::~MixStreamsOutputVideoConfig() {}

	bool MixStreamsOutputVideoConfig::operator==(
		const MixStreamsOutputVideoConfig& o) {
		if (width_ == o.width_ && height_ == o.height_ && fps_ == o.fps_ &&
			bitrate_kbps_ == o.bitrate_kbps_) {
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideoConfig::operator!=(
		const MixStreamsOutputVideoConfig& o) {
		return !(*this == o);
	}

	bool MixStreamsOutputVideoConfig::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("width") != json.end()) {
				val = json["width"];
				if (!val.is_null() && val.is_number()) {
					width_ = val.get<int>();
				}
			}

			if (json.find("height") != json.end()) {
				val = json["height"];
				if (!val.is_null() && val.is_number()) {
					height_ = val.get<int>();
				}
			}

			if (json.find("fps") != json.end()) {
				val = json["fps"];
				if (!val.is_null() && val.is_number()) {
					fps_ = val.get<int>();
				}
			}

			if (json.find("bitrate") != json.end()) {
				val = json["bitrate"];
				if (!val.is_null() && val.is_number()) {
					bitrate_kbps_ = val.get<int>();
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsOutputVideoConfig::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			if (width_ > 0) {
				json["width"] = width_;
			}
			if (height_ > 0) {
				json["height"] = height_;
			}
			if (fps_ > 0) {
				json["fps"] = fps_;
			}
			if (bitrate_kbps_ > 0) {
				json["bitrate"] = bitrate_kbps_;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideoConfig::HasValue() const {
		if (width_ <= 0 && height_ <= 0 && fps_ <= 0 && bitrate_kbps_ <= 0) {
			return false;
		}
		return true;
	}

	/************************************MixStreamsOutputVideoBackgroundPicture***************************************/

	MixStreamsOutputVideoBackgroundPicture::MixStreamsOutputVideoBackgroundPicture()
		: enable_(false), fill_mode_(PictureFillMode_Unknown) {}

	MixStreamsOutputVideoBackgroundPicture::MixStreamsOutputVideoBackgroundPicture(
		bool enable,
		uint32_t fill_mode)
		: enable_(enable), fill_mode_((PictureFillMode)fill_mode) {}

	MixStreamsOutputVideoBackgroundPicture::
		~MixStreamsOutputVideoBackgroundPicture() {}

	void MixStreamsOutputVideoBackgroundPicture::AppendBGPicture(
		const MixStreamsBGPicture& pic) {
		pictures_.push_back(pic);
	}

	bool MixStreamsOutputVideoBackgroundPicture::RemoveBGPicture(
		const MixStreamsBGPicture& pic) {
		auto it = pictures_.begin();
		while (it != pictures_.end()) {
			if (*it == pic) {
				pictures_.erase(it);
				return true;
			}
			it++;
		}
		return false;
	}

	bool MixStreamsOutputVideoBackgroundPicture::AppendBGPicture(const nlohmann::json& json) {
		MixStreamsBGPicture pic;
		if (pic.FromJson(json))
		{
			pictures_.push_back(pic);
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideoBackgroundPicture::operator==(
		const MixStreamsOutputVideoBackgroundPicture& o) {
		if (enable_ != o.enable_) {
			return false;
		}

		if (fill_mode_ != o.fill_mode_) {
			return false;
		}

		if (pictures_.size() == o.pictures_.size()) {
			auto it = pictures_.begin();
			while (it != pictures_.end()) {
				bool equ = false;
				auto oit = o.pictures_.begin();
				while (oit != o.pictures_.end()) {
					if (*it == *oit) {
						equ = true;
						break;
					}
					oit++;
				}
				if (!equ) {
					return false;
				}
				it++;
			}
		}
		else {
			return false;
		}

		return true;
	}

	bool MixStreamsOutputVideoBackgroundPicture::operator!=(
		const MixStreamsOutputVideoBackgroundPicture& o) {
		return !(*this == o);
	}

	bool MixStreamsOutputVideoBackgroundPicture::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("enable") != json.end()) {
				val = json["enable"];
				if (!val.is_null() && val.is_string()) {
					std::string str;
					val.get_to(str);
					if (str.compare("on") == 0) {
						enable_ = true;
					}
					else if (str.compare("off") == 0) {
						enable_ = false;
					}
				}
			}

			if (json.find("fillMode") != json.end()) {
				val = json["fillMode"];
				if (!val.is_null() && val.is_number()) {
					fill_mode_ = (PictureFillMode)val.get<uint32_t>();
				}
			}

			if (json.find("picture") != json.end()) {
				val = json["picture"];
				if (!val.is_null() && val.is_array()) {
					pictures_.clear();
					auto it = val.begin();
					while (it != val.end()) {
						MixStreamsBGPicture pic;
						pic.FromJson(*it);
						pictures_.push_back(pic);
						it++;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsOutputVideoBackgroundPicture::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			json["enable"] = enable_ ? "on" : "off";

			if (fill_mode_ > 0) {
				json["fillMode"] = fill_mode_;
			}

			auto it = pictures_.begin();
			while (it != pictures_.end()) {
				nlohmann::json pic;
				if (it->ToJson(&pic)) {
					json["picture"].push_back(pic);
				}
				it++;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideoBackgroundPicture::HasValue() const {
		if (fill_mode_ <= 0 && pictures_.empty()) {
			return false;
		}
		return true;
	}

	/************************************MixStreamsOutputVideo***************************************/

	MixStreamsOutputVideo::MixStreamsOutputVideo() {}

	MixStreamsOutputVideo::~MixStreamsOutputVideo() {}

	bool MixStreamsOutputVideo::operator==(const MixStreamsOutputVideo& o) {
		if (normal_config_ != o.normal_config_) {
			return false;
		}
		if (tiny_config_ != o.tiny_config_) {
			return false;
		}
		if (background_color_.compare(o.background_color_)) {
			return false;
		}
		if (exparams_.render_mode_ != o.exparams_.render_mode_) {
			return false;
		}
		if (background_picture_ != o.background_picture_) {
			return false;
		}
		return true;
	}

	bool MixStreamsOutputVideo::operator!=(const MixStreamsOutputVideo& o) {
		return !(*this == o);
	}

	bool MixStreamsOutputVideo::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("backgroundColor") != json.end()) {
				val = json["backgroundColor"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(background_color_);
				}
			}

			if (json.find("normal") != json.end()) {
				val = json["normal"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutputVideoConfig nor;
					if (nor.FromJson(val)) {
						normal_config_ = nor;
					}
				}
			}

			if (json.find("tiny") != json.end()) {
				val = json["tiny"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutputVideoConfig tiny;
					if (tiny.FromJson(val)) {
						tiny_config_ = tiny;
					}
				}
			}

			if (json.find("exparams") != json.end()) {
				val = json["exparams"];
				if (!val.is_null() && val.is_object()) {
					VideoExparams exparams;
					if (exparams.FromJson(val)) {
						exparams_ = exparams;
					}
				}
			}

			if (json.find("backgroundPicture") != json.end()) {
				val = json["backgroundPicture"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutputVideoBackgroundPicture pic;
					if (pic.FromJson(val)) {
						background_picture_ = pic;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsOutputVideo::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			if (normal_config_.HasValue()) {
				nlohmann::json nor;
				if (normal_config_.ToJson(&nor)) {
					json["normal"] = nor;
				}
			}

			if (tiny_config_.HasValue()) {
				nlohmann::json tiny;
				if (tiny_config_.ToJson(&tiny)) {
					json["tiny"] = tiny;
				}
			}

			if (!background_color_.empty()) {
				json["backgroundColor"] = background_color_;
			}

			if (exparams_.render_mode_ > 0) {
				json["exparams"] = exparams_.ToJson();
			}

			if (background_picture_.HasValue()) {
				nlohmann::json pic;
				if (background_picture_.ToJson(&pic)) {
					json["backgroundPicture"] = pic;
				}
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideo::HasValue() const {
		if (!normal_config_.HasValue() && !tiny_config_.HasValue() &&
			background_color_.empty() && !background_picture_.HasValue()) {
			return false;
		}
		return true;
	}

	void MixStreamsOutputVideo::SetBackgroundColor(const std::string& hex_color) {
		background_color_ = hex_color;
	}

	void MixStreamsOutputVideo::SetVideoRenerMode(VideoRenderMode mode) {
		exparams_.render_mode_ = mode;
	}

	bool MixStreamsOutputVideo::SetNormalVideoConfig(const nlohmann::json& json) {
		MixStreamsOutputVideoConfig nor;
		if (nor.FromJson(json))
		{
			normal_config_ = nor;
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideo::SetTinyVideoConfig(const nlohmann::json& json) {
		MixStreamsOutputVideoConfig tiny;
		if (tiny.FromJson(json))
		{
			tiny_config_ = tiny;
			return true;
		}
		return false;
	}

	bool MixStreamsOutputVideo::SetBackgroundPicture(const nlohmann::json& json)
	{
		MixStreamsOutputVideoBackgroundPicture pic;
		if (pic.FromJson(json))
		{
			background_picture_ = pic;
			return true;
		}
		return false;
	}

	nlohmann::json MixStreamsOutputVideo::VideoExparams::ToJson() {
		nlohmann::json val;
		if (render_mode_ > 0) {
			val["renderMode"] = render_mode_;
		}
		return val;
	}

	bool MixStreamsOutputVideo::VideoExparams::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			if (json.find("renderMode") != json.end()) {
				nlohmann::json val = json["renderMode"];
				if (!val.is_null() && val.is_number()) {
					render_mode_ = (VideoRenderMode)val.get<uint32_t>();
					return true;
				}
			}
		}
		return false;
	}

	/************************************MixStreamsOutput***************************************/

	MixStreamsOutput::MixStreamsOutput() {}

	MixStreamsOutput::MixStreamsOutput(const MixStreamsOutput& o) {
		*this = o;
	}

	MixStreamsOutput& MixStreamsOutput::operator=(const MixStreamsOutput& o) {
		audio_ = o.audio_;
		video_ = o.video_;
		return *this;
	}

	MixStreamsOutput::~MixStreamsOutput() {}

	bool MixStreamsOutput::operator==(const MixStreamsOutput& o) {
		if (audio_ != o.audio_) {
			return false;
		}

		if (video_ != o.video_) {
			return false;
		}

		return true;
	}

	bool MixStreamsOutput::operator!=(const MixStreamsOutput& o) {
		return !(*this == o);
	}

	bool MixStreamsOutput::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("audio") != json.end()) {
				val = json["audio"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutputAudio audio;
					if (audio.FromJson(val)) {
						audio_ = audio;
					}
				}
			}

			if (json.find("video") != json.end()) {
				val = json["video"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutputVideo video;
					if (video.FromJson(val)) {
						video_ = video;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsOutput::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			if (audio_.HasValue()) {
				nlohmann::json audio;
				if (audio_.ToJson(&audio)) {
					json["audio"] = audio;
				}
			}

			if (video_.HasValue()) {
				nlohmann::json video;
				if (video_.ToJson(&video)) {
					json["video"] = video;
				}
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsOutput::HasValue() const {
		if (!audio_.HasValue() && !video_.HasValue()) {
			return false;
		}
		return true;
	}

	bool MixStreamsOutput::SetAudio(const nlohmann::json& json) {
		MixStreamsOutputAudio audio;
		if (audio.FromJson(json))
		{
			audio_ = audio;
			return true;
		}
		return false;
	}

	bool MixStreamsOutput::SetVideo(const nlohmann::json& json) {
		MixStreamsOutputVideo video;
		if (video.FromJson(json))
		{
			video_ = video;
			return true;
		}
		return false;
	}

	/************************************MixStreamsMixRooms***************************************/

	MixStreamsMixRooms::MixStreamsMixRooms() {}

	MixStreamsMixRooms::MixStreamsMixRooms(const MixStreamsMixRooms& o) {
		*this = o;
	}

	MixStreamsMixRooms& MixStreamsMixRooms::operator=(const MixStreamsMixRooms& o) {
		mix_rooms.clear();
		auto it = o.mix_rooms.begin();
		while (it != o.mix_rooms.end()) {
			mix_rooms.push_back(*it);
			it++;
		}
		return *this;
	}

	MixStreamsMixRooms::~MixStreamsMixRooms() {}

	bool MixStreamsMixRooms::operator==(const MixStreamsMixRooms& o) {
		if (mix_rooms.size() == o.mix_rooms.size()) {
			auto it = mix_rooms.begin();
			while (it != mix_rooms.end()) {
				bool equ = false;
				auto oit = o.mix_rooms.begin();
				while (oit != o.mix_rooms.end()) {
					if (*it == *oit) {
						equ = true;
					}
					oit++;
				}
				if (!equ) {
					return false;
				}
				it++;
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool MixStreamsMixRooms::operator!=(const MixStreamsMixRooms& o) {
		return !(*this == o);
	}

	bool MixStreamsMixRooms::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("mixRooms") != json.end()) {
				val = json["mixRooms"];
				if (!val.is_null() && val.is_array()) {
					auto it = val.begin();
					while (it != val.end()) {
						std::string room;
						(*it).get_to(room);
						mix_rooms.push_back(room);
						it++;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsMixRooms::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			auto it = mix_rooms.begin();
			while (it != mix_rooms.end()) {
				json["mixRooms"].push_back(*it);
				it++;
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsMixRooms::HasValue() const {
		if (mix_rooms.empty()) {
			return false;
		}
		return true;
	}

	void MixStreamsMixRooms::AppendRoom(const std::string& room) {
		if (!room.empty()) {
			mix_rooms.push_back(room);
		}
	}

	bool MixStreamsMixRooms::RemoveRoom(const std::string& room) {
		auto it = mix_rooms.begin();
		while (it != mix_rooms.end()) {
			if (it->compare(room) == 0) {
				mix_rooms.erase(it);
				return true;
			}
			it++;
		}
		return false;
	}

	/************************************MixStreamsWaterMark***************************************/

	MixStreamsWaterMark::MixStreamsWaterMark() :enable_(false) {}

	MixStreamsWaterMark::~MixStreamsWaterMark() {}

	bool MixStreamsWaterMark::operator==(const MixStreamsWaterMark& o) {
		return false;
	}

	bool MixStreamsWaterMark::operator!=(const MixStreamsWaterMark& o) {
		return !(*this == o);
	}

	bool MixStreamsWaterMark::FromJson(const nlohmann::json& json) {
		return false;
	}

	bool MixStreamsWaterMark::ToJson(nlohmann::json* json) {
		return true;
	}

	bool MixStreamsWaterMark::HasValue() const {
		return false;
	}

	/************************************MixStreamsLayout***************************************/

	MixStreamsLayout::MixStreamsLayout()
		: version_(MCU_VERSION),
		custom_mode_(false),
		input_filter_mode_(INVALID_VALUE),
		mode_(MixStreamMode_Unknown) {}

	MixStreamsLayout::MixStreamsLayout(const MixStreamsLayout& o) {
		*this = o;
	}

	MixStreamsLayout& MixStreamsLayout::operator=(const MixStreamsLayout& o) {
		version_ = o.version_;
		custom_mode_ = o.custom_mode_;
		input_filter_mode_ = o.input_filter_mode_;
		mode_ = o.mode_;
		host_user_id_ = o.host_user_id_;
		host_stream_id_ = o.host_stream_id_;
		input_ = o.input_;
		output_ = o.output_;
		mix_rooms_ = o.mix_rooms_;
		water_mark_ = o.water_mark_;

		return *this;
	}

	MixStreamsLayout::~MixStreamsLayout() {}

	void MixStreamsLayout::SetVersion(int version) {
		version_ = version;
	}

	void MixStreamsLayout::SetCustomMode(bool custom_mode) {
		custom_mode_ = custom_mode;
	}

	void MixStreamsLayout::SetInputFilterMode(int mode) {
		input_filter_mode_ = mode;
	}

	void MixStreamsLayout::SetMixStreamMode(uint32_t mix_stream_mode) {
		MixStreamMode mode = (MixStreamMode)mix_stream_mode;
		if (mode <= MixStreamMode_Unknown || mode > MixStreamMode_Fix) {
			mode_ = MixStreamMode_Unknown;
		}
		else {
			mode_ = mode;
		}
	}

	void MixStreamsLayout::SetHostUserId(const std::string& user_id) {
		host_user_id_ = user_id;
	}

	void MixStreamsLayout::SetHostStreamId(const std::string& stream_id) {
		host_stream_id_ = stream_id;
	}

	bool MixStreamsLayout::SetInput(const nlohmann::json& json) {
		MixStreamsInput input;
		if (input.FromJson(json))
		{
			input_ = input;
			return true;
		}
		return false;
	}

	bool MixStreamsLayout::SetOutput(const nlohmann::json& json) {
		MixStreamsOutput output;
		if (output.FromJson(json))
		{
			output_ = output;
			return true;
		}
		return false;
	}

	bool MixStreamsLayout::SetMixRooms(const nlohmann::json& json) {
		MixStreamsMixRooms rooms;
		if (rooms.FromJson(json))
		{
			mix_rooms_ = rooms;
			return true;
		}
		return false;
	}

	bool MixStreamsLayout::SetWaterMark(const nlohmann::json& json) {
		MixStreamsWaterMark water_mark;
		if (water_mark.FromJson(json))
		{
			water_mark_ = water_mark;
			return true;
		}
		return false;
	}

	bool MixStreamsLayout::FromJson(const nlohmann::json& json) {
		if (!json.is_null()) {
			nlohmann::json val;

			if (json.find("version") != json.end()) {
				val = json["version"];
				if (!val.is_null() && val.is_number()) {
					version_ = val.get<int>();
				}
			}

			if (json.find("mode") != json.end()) {
				val = json["mode"];
				if (!val.is_null() && val.is_number()) {
					mode_ = (MixStreamMode)val.get<uint32_t>();
				}
			}

			if (json.find("customMode") != json.end()) {
				val = json["customMode"];
				if (!val.is_null() && val.is_boolean()) {
					custom_mode_ = val.get<bool>();
				}
			}

			if (json.find("inputFilterMode") != json.end()) {
				val = json["inputFilterMode"];
				if (!val.is_null() && val.is_number()) {
					input_filter_mode_ = val.get<int>();
				}
			}

			if (json.find("host_user_id") != json.end()) {
				val = json["host_user_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(host_user_id_);
				}
			}

			if (json.find("host_stream_id") != json.end()) {
				val = json["host_stream_id"];
				if (!val.is_null() && val.is_string()) {
					val.get_to(host_stream_id_);
				}
			}

			if (json.find("input") != json.end()) {
				val = json["input"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsInput input;
					if (input.FromJson(val)) {
						input_ = input;
					}
				}
			}

			if (json.find("output") != json.end()) {
				val = json["output"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsOutput output;
					if (output.FromJson(val)) {
						output_ = output;
					}
				}
			}

			if (json.find("mixRooms") != json.end()) {
				val = json["mixRooms"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsMixRooms mix_rooms;
					if (mix_rooms.FromJson(val)) {
						mix_rooms_ = mix_rooms;
					}
				}
			}

			if (json.find("waterMark") != json.end()) {
				val = json["waterMark"];
				if (!val.is_null() && val.is_object()) {
					MixStreamsWaterMark water_mark;
					if (water_mark.FromJson(val)) {
						water_mark_ = water_mark;
					}
				}
			}

			return true;
		}

		return false;
	}

	bool MixStreamsLayout::ToJson(nlohmann::json* pjson) {
		if (pjson && HasValue()) {
			nlohmann::json json;

			if (version_ > 0) {
				json["version"] = version_;
			}

			if (mode_ > MixStreamMode_Unknown) {
				json["mode"] = mode_;
			}

			json["customMode"] = custom_mode_;

			if (input_filter_mode_ >= 0) {
				json["inputFilterMode"] = input_filter_mode_;
			}

			if (!host_user_id_.empty()) {
				json["host_user_id"] = host_user_id_;
			}

			if (!host_stream_id_.empty()) {
				json["host_stream_id"] = host_stream_id_;
			}

			if (input_.HasValue()) {
				nlohmann::json input;
				if (input_.ToJson(&input)) {
					json["input"] = input;
				}
			}

			if (output_.HasValue()) {
				nlohmann::json output;
				if (output_.ToJson(&output)) {
					json["output"] = output;
				}
			}

			if (mix_rooms_.HasValue()) {
				nlohmann::json rooms;
				if (mix_rooms_.ToJson(&rooms)) {
					json["mixRooms"] = rooms;
				}
			}

			if (water_mark_.HasValue()) {
				nlohmann::json water_mark;
				if (water_mark_.ToJson(&water_mark)) {
					json["waterMark"] = water_mark;
				}
			}

			*pjson = json;
			return true;
		}
		return false;
	}

	bool MixStreamsLayout::HasValue() const {
		if (version_ <= 0 && mode_ <= MixStreamMode_Unknown &&
			input_filter_mode_ < 0 && host_user_id_.empty() &&
			host_stream_id_.empty() && !input_.HasValue() && !output_.HasValue() &&
			!mix_rooms_.HasValue() && !water_mark_.HasValue()) {
			return false;
		}
		return true;
	}


	/************************************MixStreamsLayoutManager***************************************/

	MixStreamsLayoutManager::MixStreamsLayoutManager() {}

	MixStreamsLayoutManager::~MixStreamsLayoutManager() {}

	MixStreamsLayoutManager* MixStreamsLayoutManager::GetInst() {
		static MixStreamsLayoutManager inst;
		return &inst;
	}

	void MixStreamsLayoutManager::SetMixStreamsLayout(
		const MixStreamsLayout& layout) {
		mix_layout_ = layout;
	}

	MixStreamsLayout MixStreamsLayoutManager::GetMixStreamsLayout() const {
		return mix_layout_;
	}

	bool MixStreamsLayoutManager::SetMixStreamsLayout(
		const std::string& layout_json) {
		MixStreamsLayout layout;
		if (layout.FromJsonString(layout_json)) {
			mix_layout_ = layout;
			return true;
		}
		return false;
	}

	std::string MixStreamsLayoutManager::GetMixStreamsLayoutString() {
		std::string json_str;
		if (mix_layout_.ToJsonString(&json_str)) {
			return json_str;
		}
		return std::string();
	}

	/************************************MixStreamsLayoutDemo***************************************/

    bool MixStreamsLayoutDemo::MixStreamLayout(const std::string& roomId, const std::string& localUser, const std::string& userId)
	{
		int32_t ret = 0;
		std::string json_str;
		nlohmann::json json;
		MixStreamsOutputVideoConfig norm_config(480, 360, 15, 500);
		MixStreamsOutputVideoConfig tiny_config(160, 120, 15, 250);
		MixStreamsOutputAudio audioOutput(128);

		MixStreamsOutputVideo videoOutput;
		videoOutput.SetBackgroundColor("0x778899");
		videoOutput.SetVideoRenerMode(VideoRenderMode_Scale_By_Ratio);

		MixStreamsBGPicture pic(0.0, 0.0, 0.4, 0.6, "https://pics1.baidu.com/feed/503d269759ee3d6d28cf1f1e64748e2a4e4ade41?token=0f9c25c9ef80e1e5702d57f1e4a2d8d1&f=png");
		MixStreamsBGPicture pic2(0.4, 0.6, 0.6, 0.4, "https://pics2.baidu.com/feed/29381f30e924b89901372b8d4464fe9d0b7bf6e3?token=f2312ce4ee1a96c6a2e60d84aacc0ed2&f=jpeg");
		MixStreamsOutputVideoBackgroundPicture bg_pic(true, PictureFillMode_Crop_By_Ratio);

		if (pic.ToJson(&json))
		{
			bg_pic.AppendBGPicture(json);
		}
		if (pic2.ToJson(&json))
		{
			bg_pic.AppendBGPicture(json);
		}
		if (norm_config.ToJson(&json))
		{
			videoOutput.SetNormalVideoConfig(json);
		}
		if (tiny_config.ToJson(&json))
		{
			videoOutput.SetTinyVideoConfig(json);
		}
		if (bg_pic.ToJson(&json))
		{
			videoOutput.SetBackgroundPicture(json);
		}

		MixStreamsOutput output;
		if (audioOutput.ToJson(&json))
		{
			output.SetAudio(json);
		}
		if (videoOutput.ToJson(&json))
		{
			output.SetVideo(json);
		}

        std::string local_id = localUser;
        std::string local_stream_id = local_id + std::string("_RongCloudRTC");
        std::string remote_id = userId;
        std::string remote_stream_id = remote_id + std::string("_RongCloudRTC");
        MixStreamsInputVideo videoInput(0, 0, 150, 150, local_id.c_str(), local_stream_id.c_str());
        MixStreamsInputAudio audioInput(local_id.c_str(), local_stream_id.c_str());
        MixStreamsInputVideo videoInput2(200, 200, 150, 150, remote_id, remote_stream_id.c_str());
        MixStreamsInputAudio audioInput2(remote_id, remote_stream_id.c_str());

		MixStreamsInput input;
		if (audioInput.ToJson(&json))
		{
			input.AppendAudio(json);
		}
		if (audioInput2.ToJson(&json))
		{
			input.AppendAudio(json);
		}
		if (videoInput.ToJson(&json))
		{
			input.AppendVideo(json);
		}
		if (videoInput2.ToJson(&json))
		{
			input.AppendVideo(json);
		}

		static int mode_index = MixStreamMode_Custom;
		MixStreamsLayout layout;
		layout.SetCustomMode(0);
		layout.SetMixStreamMode(mode_index);
		if (input.ToJson(&json))
		{
			layout.SetInput(json);
		}
		if (output.ToJson(&json))
		{
			layout.SetOutput(json);
		}
		if (layout.ToJsonString(&json_str))
		{
            ret = rcrtc_set_mix_stream_config(roomId.c_str(), json_str.c_str(), MixStreamsLayoutDemo::MixStreamLayoutCallback, nullptr);
		}
		mode_index++;
		if (mode_index > MixStreamMode_Fix)
		{
			mode_index = MixStreamMode_Custom;
		}
		return ret == 0;
	}

	void MixStreamsLayoutDemo::MixStreamLayoutCallback(enum_rcrtc_code code,
		const char* json,
		HANDLE context) {
        //logd("MixStreamsLayoutDemo::MixStreamLayoutCallback %d, %s", code, json ? json : "null");
	}

}  // namespace rc
