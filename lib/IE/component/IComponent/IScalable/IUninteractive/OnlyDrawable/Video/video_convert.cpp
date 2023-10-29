#include "video_convert.hpp"
#ifdef IE_ImageMagick_FOUND
#include "VideoFromFile/VideoFromFile.hpp"
#endif
#include "VideoFromTexture/VideoFromTexture.hpp"
#include "IE/modules/yaml-cpp/file-buffer/FileBuffer.hpp"

namespace ie {
	bool is_video(std::string path) {
		std::array<std::string, 8> arr{".bmp", ".png", ".jpg", ".tga", ".dds", ".psd", ".hdr", ".pic"};
		std::string str{path.begin() + path.rfind('.'), path.end()};
		return std::count(arr.begin(), arr.end(), str) == 0;
	}
	
	/*old_yaml
	bool video_convert(const YAML::Node& node, OnlyDrawable*& video) {
#ifdef IE_ImageMagick_FOUND
		if(!node["offset"] && is_video(node["path"].as<std::string>())) {
			video = new VideoFromFile{
				*node["path"].as<std::vector<sf::Texture>*>(),
				Buffer::get<SCoefficientValue>(node["viewing-progress"])
			};
		} else {
#endif
		video = new VideoFromTexture{
			*node["path"].as<sf::Texture*>(),
			Buffer::get<SCoefficientValue>(node["viewing-progress"]),
			conv_def(node["rect"], sf::IntRect{0, 0, 0, 0}),
			conv_def(node["count-frame"], 0u),
			conv_def(node["offset"], sf::Vector2i{0, 0}),
		};
#ifdef IE_ImageMagick_FOUND
		}
#endif
		return true;
	}
	*/
}