/**
 * Copyright © 2021, RongCloud.
 * All rights reserved.
 *
 * All the contents are the copyright of RongCloud Network Technology Co.Ltd.
 * Unless otherwise credited. http://rongcloud.cn
 *
 */
#ifndef RCRTCLIB_SRC_CORE_LIBC_LIBC_MIX_STREAMS_LAYOUT_H_
#define RCRTCLIB_SRC_CORE_LIBC_LIBC_MIX_STREAMS_LAYOUT_H_

 /*合流布局说明：
 一、MixStreamsLayout类是生成合流布局json串根类，它的成员与合流布局的json的子字段基本一一对应。

 二、每个类的成员变量的值基本有两种输入方式：
 1）、从构造函数中输入，比如MixStreamsOutputVideoConfig类的四个成员变量就可以通过构造函数输入；
 2）、从对应的类方法输入，比如MixStreamsOutputVideoConfig类也可以通过FromJson函数从一个json对象输入，再比如MixStreamsLayout类的version_
 成员通过SetVersion方法直接设置输入。MixStreamsLayout类的input_成员可以通过SetInput方法从外部一个json对象直接设置导入。

 三、每个类对象都有如下五个成员函数：
	 virtual bool FromJson(const nlohmann::json& json);
	 virtual bool FromJsonString(const std::string& json_str);
	 virtual bool ToJson(nlohmann::json* json);
	 virtual bool ToJsonString(std::string* json_str);
	 virtual bool HasValue() const;
 它们可以从json导入对应的成员变量值，也可以从一个合法的json字符串来导入对应所有成员变量值；还可以把类对象的成员值导出为json对象或json字符串。
 HasValue成员函数的作用是判断某个对象是否有合法值，如果没有合法值，在MixStreamsLayout类生成请求字符串的时候，就不会生成这个对象对应的请求字段，
 比如：MixStreamsInputVideo对象的五个成员变量都是不合法的值(x_ < 0 && y_ < 0 && width_ <= 0 && height_ <= 0 && user_id_.empty() && stream_id_.empty())
 那么在生成的合流布局请求json串中就不会有"input"json对象下的"video"子json串对象。
 */

 /*
 {//class MixStreamsLayout
	 "version": 2, //int version_;
	 "customMode": true, //bool custom_mode_;
	 "mode": 1, //MixStreamMode mode_;  //值可以是1/2/3,  1 自定义,需要用户设置input； 2 悬浮(默认) ； 3 自适应
	 "inputFilterMode" : 0, //int input_filter_mode_;
	 "host_user_id": "001", //std::string host_user_id_;
	 "host_stream_id": "111_RongCloudRTC", //std::string host_stream_id_;  //此流会渲染到布局的主位置上
	 "output": //class MixStreamsOutput (MixStreamsOutput output_);
	 {
		 "video": //class MixStreamsOutputVideo
		 {
			 "normal": //class MixStreamsOutputVideoConfig
			 {
				 "width": 360,
				 "height": 640,
				 "fps": 25,
				 "bitrate": 800
			 },
			 "tiny": //class MixStreamsOutputVideoConfig
			 {
				 "width": 180,
				 "height": 320,
				 "fps": 15,
				 "bitrate": 200
			 },
			 "exparams": //VideoExparams exparams_;
			 {
				 "renderMode": 1  //VideoRenderMode render_mode_;  //1 裁剪; 2 不裁剪,根据该用户分辨率进行渲染
			 },
			 "backgroundColor": "0xf1a2c3", //std::string background_color_;  //背景颜色, 无此项则保持上次设置
			 "backgroundPicture": //class MixStreamsOutputVideoBackgroundPicture  //背景图片, 无此项则保持上次设置
			 {
				 "enable": "on", //bool enable_;  //enable: off-关闭; on或者没有, 开启
				 "fillMode": 1,//PictureFillMode fill_mode_;  //背景图片填充模式, 1-按比例裁剪; 2-不裁剪, 按比例压缩
				 "picture": //class MixStreamsBGPicture
				 [//如果有多个图片时，服务器是按平铺（一个挨着一个），总的水平偏移、垂直偏移以及宽高之和不能超过0.0--1.0这个范围
					 {
						 "uri": "http://aaa.png", //png图片下载地址
						 "x": 0.0,  //相对于整体画布的起始位置x坐标(百分比，0.0--1.0之间)
						 "y": 0.0,  //相对于整体画布的起始位置x坐标(百分比，0.0--1.0之间)
						 "w": 0.5,  //相对于整体画布的宽(百分比，0.0--1.0之间)，如果有多个图片，多个图片宽的百分比之和不能超过1.0
						 "h": 0.5   //相对于整体画布的高(百分比，0.0--1.0之间)，如果有多个图片，多个图片高的百分比之和不能超过1.0
					 },
					 {
						 "uri": "http://bbb.png",
						 "x": 0.5,
						 "y": 0.5,
						 "w": 0.5,
						 "h": 0.5
					 }
				 ]
			 }
		 },
		 "audio": //class MixStreamsOutputAudio
		 {
			 "bitrate": 200  //kbps
		 }
	 },
	 "input": //class MixStreamsInput (MixStreamsInput input_);
	 {
		 "video": //MixStreamsInputVideo
		 [
			 {
				 "user_id": "111",
				 "stream_id": "111_RongCloudRTC",  //用来区分普通视频和第三方视频,无此项或者值为RongCloudRTC时为普通摄像头视频
				 "x": 0,
				 "y": 0,
				 "width": 180,
				 "height": 320
			 },
			 {
				 "user_id": "2222",
				 "stream_id": "2222_screenshare",
				 "x": 180,
				 "y": 320,
				 "width": 180,
				 "height": 320
			 }
		 ],
		 "audio": //MixStreamsInputAudio
		 [
			 {
				 "user_id": "111",
				 "stream_id": "111_RongCloudRTC"
			 },
			 {
				 "user_id": "2222",
				 "stream_id": "2222_RongCloudRTC"
			 }
		 ]
	 },
	 "mixRooms": //class MixStreamsMixRooms
	 [
		 "room1",
		 "room2",
		 "room3"
	 ]
 }

 //MixStreamsLayoutDemo生成的json字符串如下：
 {
	 "customMode": false,
	 "input": {
		 "video": [{
			 "height": 150,
			 "stream_id": "qqqq_RongCloudRTC",
			 "user_id": "qqqq",
			 "width": 150,
			 "x": 0,
			 "y": 0
		 }, {
			 "height": 150,
			 "stream_id": "eeee_RongCloudRTC",
			 "user_id": "eeee",
			 "width": 150,
			 "x": 200,
			 "y": 200
		 }]
	 },
	 "mode": 2,
	 "output": {
		 "audio": {
			 "bitrate": 128
		 },
		 "video": {
			 "backgroundColor": "0x778899",
			 "exparams": {
				 "renderMode": 2
			 },
			 "normal": {
				 "bitrate": 500,
				 "fps": 15,
				 "height": 360,
				 "width": 480
			 },
			 "tiny": {
				 "bitrate": 250,
				 "fps": 15,
				 "height": 120,
				 "width": 160
			 }
		 }
	 },
	 "version": 2
 }
 */

#include <map>
#include <string>
#include <vector>
#include <libc_rtc_types.h>
#include "nlohmann_json.hpp"


namespace rc_mix_test {
	static const int MCU_VERSION = 2;
	static const int INVALID_VALUE = -1;

	class JsonTransform {
	public:
		virtual bool FromJson(const nlohmann::json& json);
		virtual bool FromJsonString(const std::string& json_str);
		virtual bool ToJson(nlohmann::json* json);
		virtual bool ToJsonString(std::string* json_str);
		virtual bool HasValue() const;

	protected:
		virtual ~JsonTransform() {}
	};

	typedef enum VideoRenderMode {
		VideoRenderMode_Unknown = 0,
		VideoRenderMode_Crop = 1,
		VideoRenderMode_Scale_By_Ratio = 2,
	} VideoRenderMode;

	typedef enum PictureFillMode {
		PictureFillMode_Unknown = 0,
		PictureFillMode_Crop_By_Ratio = 1,
		PictureFillMode_Scale_By_Ratio = 2,
	} PictureFillMode;

	typedef enum MixStreamMode {
		MixStreamMode_Unknown = 0,
		MixStreamMode_Custom = 1,
		MixStreamMode_Suspension = 2,
		MixStreamMode_Fix = 3,
	} MixStreamMode;

	class MixStreamsBGPicture : public JsonTransform {
	public:
		MixStreamsBGPicture();
		MixStreamsBGPicture(float x, float y, float w, float h, const std::string& uri);
		~MixStreamsBGPicture() override;

		bool operator==(const MixStreamsBGPicture& o);
		bool operator!=(const MixStreamsBGPicture& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		float x_;
		float y_;
		float w_;
		float h_;
		std::string uri_;
	};

	class MixStreamsInputAudio : public JsonTransform {
	public:
		MixStreamsInputAudio();
		MixStreamsInputAudio(const std::string& user_id,
			const std::string& stream_id);
		~MixStreamsInputAudio() override;

		bool operator==(const MixStreamsInputAudio& o);
		bool operator!=(const MixStreamsInputAudio& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		std::string user_id_;
		std::string stream_id_;
	};

	class MixStreamsInputVideo : public JsonTransform {
	public:
		MixStreamsInputVideo();
		MixStreamsInputVideo(int x,
			int y,
			int w,
			int h,
			const std::string& user_id,
			const std::string& stream_id);
		MixStreamsInputVideo(const MixStreamsInputVideo& o);
		MixStreamsInputVideo& operator=(const MixStreamsInputVideo& o);
		~MixStreamsInputVideo() override;

		bool operator==(const MixStreamsInputVideo& o);
		bool operator!=(const MixStreamsInputVideo& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		int x_;
		int y_;
		int width_;
		int height_;
		std::string user_id_;
		std::string stream_id_;
	};

	class MixStreamsInput : public JsonTransform {
	public:
		MixStreamsInput();
		MixStreamsInput(const MixStreamsInput& o);
		MixStreamsInput& operator=(const MixStreamsInput& o);
		~MixStreamsInput() override;

		bool operator==(const MixStreamsInput& o);
		bool operator!=(const MixStreamsInput& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

		bool AppendAudio(const nlohmann::json& json);
		bool AppendVideo(const nlohmann::json& json);

	protected:
		std::vector<MixStreamsInputAudio> audios_;
		std::vector<MixStreamsInputVideo> videos_;
	};

	class MixStreamsOutputAudio : public JsonTransform {
	public:
		MixStreamsOutputAudio();
		explicit MixStreamsOutputAudio(int bitrate_kbps);
		~MixStreamsOutputAudio() override;

		bool operator==(const MixStreamsOutputAudio& o);
		bool operator!=(const MixStreamsOutputAudio& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		int bitrate_kbps_;
	};

	class MixStreamsOutputVideoConfig : public JsonTransform {
	public:
		MixStreamsOutputVideoConfig();
		MixStreamsOutputVideoConfig(int w, int h, int fps, int b);
		~MixStreamsOutputVideoConfig() override;

		bool operator==(const MixStreamsOutputVideoConfig& o);
		bool operator!=(const MixStreamsOutputVideoConfig& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	private:
		int width_;
		int height_;
		int fps_;
		int bitrate_kbps_;
	};

	class MixStreamsOutputVideoBackgroundPicture : public JsonTransform {
	public:
		MixStreamsOutputVideoBackgroundPicture();
		MixStreamsOutputVideoBackgroundPicture(bool enable, uint32_t fill_mode);
		~MixStreamsOutputVideoBackgroundPicture() override;

		void AppendBGPicture(const MixStreamsBGPicture& pic);
		bool RemoveBGPicture(const MixStreamsBGPicture& pic);
		bool AppendBGPicture(const nlohmann::json& json);

		bool operator==(const MixStreamsOutputVideoBackgroundPicture& o);
		bool operator!=(const MixStreamsOutputVideoBackgroundPicture& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		bool enable_;
		PictureFillMode fill_mode_;
		std::vector<MixStreamsBGPicture> pictures_;
	};

	class MixStreamsOutputVideo : public JsonTransform {
	public:
		MixStreamsOutputVideo();
		~MixStreamsOutputVideo() override;

		bool operator==(const MixStreamsOutputVideo& o);
		bool operator!=(const MixStreamsOutputVideo& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

		void SetBackgroundColor(const std::string& hex_color);
		void SetVideoRenerMode(VideoRenderMode mode);
		bool SetNormalVideoConfig(const nlohmann::json& json);
		bool SetTinyVideoConfig(const nlohmann::json& json);
		bool SetBackgroundPicture(const nlohmann::json& json);

	protected:
		struct VideoExparams {
			VideoRenderMode render_mode_;
			nlohmann::json ToJson();
			bool FromJson(const nlohmann::json& json);

			VideoExparams() : render_mode_(VideoRenderMode_Crop) {}
			explicit VideoExparams(VideoRenderMode mode) : render_mode_(mode) {}
		};

		MixStreamsOutputVideoConfig normal_config_;
		MixStreamsOutputVideoConfig tiny_config_;
		std::string background_color_;
		VideoExparams exparams_;
		MixStreamsOutputVideoBackgroundPicture background_picture_;
	};

	class MixStreamsOutput : public JsonTransform {
	public:
		MixStreamsOutput();
		MixStreamsOutput(const MixStreamsOutput& o);
		MixStreamsOutput& operator=(const MixStreamsOutput& o);
		~MixStreamsOutput() override;

		bool operator==(const MixStreamsOutput& o);
		bool operator!=(const MixStreamsOutput& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

		bool SetAudio(const nlohmann::json& json);
		bool SetVideo(const nlohmann::json& json);

	protected:
		MixStreamsOutputAudio audio_;
		MixStreamsOutputVideo video_;
	};

	class MixStreamsMixRooms : public JsonTransform {
	public:
		MixStreamsMixRooms();
		MixStreamsMixRooms(const MixStreamsMixRooms& o);
		MixStreamsMixRooms& operator=(const MixStreamsMixRooms& o);
		~MixStreamsMixRooms() override;

		bool operator==(const MixStreamsMixRooms& o);
		bool operator!=(const MixStreamsMixRooms& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

		void AppendRoom(const std::string& room);
		bool RemoveRoom(const std::string& room);

	protected:
		std::vector<std::string> mix_rooms;
	};

	class MixStreamsWaterMark : public JsonTransform {
	public:
		MixStreamsWaterMark();
		~MixStreamsWaterMark() override;

		bool operator==(const MixStreamsWaterMark& o);
		bool operator!=(const MixStreamsWaterMark& o);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		bool enable_;
	};

	class MixStreamsLayout : public JsonTransform {
	public:
		MixStreamsLayout();
		MixStreamsLayout(const MixStreamsLayout& o);
		MixStreamsLayout& operator=(const MixStreamsLayout& o);
		~MixStreamsLayout() override;

		void SetVersion(int version);
		void SetCustomMode(bool custom_mode);
		void SetInputFilterMode(int mode);
		void SetMixStreamMode(uint32_t mix_stream_mode);
		void SetHostUserId(const std::string& user_id);
		void SetHostStreamId(const std::string& stream_id);

		bool SetInput(const nlohmann::json& json);
		bool SetOutput(const nlohmann::json& json);
		bool SetMixRooms(const nlohmann::json& json);
		bool SetWaterMark(const nlohmann::json& json);

		bool FromJson(const nlohmann::json& json) override;
		bool ToJson(nlohmann::json* json) override;
		bool HasValue() const override;

	protected:
		int version_;
		bool custom_mode_;
		int input_filter_mode_;
		MixStreamMode mode_;
		std::string host_user_id_;
		std::string host_stream_id_;
		MixStreamsInput input_;
		MixStreamsOutput output_;
		MixStreamsMixRooms mix_rooms_;
		MixStreamsWaterMark water_mark_;
	};


	class MixStreamsLayoutManager {
	public:
		~MixStreamsLayoutManager();
		static MixStreamsLayoutManager* GetInst();

		void SetMixStreamsLayout(const MixStreamsLayout& layout);
		MixStreamsLayout GetMixStreamsLayout() const;

		bool SetMixStreamsLayout(const std::string& layout_json);
		std::string GetMixStreamsLayoutString();

	private:
		MixStreamsLayoutManager();

	private:
		MixStreamsLayout mix_layout_;
	};

	class MixStreamsLayoutDemo {
	public:
        MixStreamsLayoutDemo() {}
		~MixStreamsLayoutDemo() {}

        static bool MixStreamLayout(const std::string& roomId, const std::string& localUser, const std::string& userId);
		static void MixStreamLayoutCallback(enum_rcrtc_code code,
			const char* json,
			HANDLE context);
	};

}  // namespace rc_mix_test

#endif  // RCRTCLIB_SRC_CORE_LIBC_LIBC_MIX_STREAMS_LAYOUT_H_
