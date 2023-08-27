#include "videoConvert.hpp"
#include "VideoFromFile/VideoFromFile.hpp"
#include "VideoFromTexture/VideoFromTexture.hpp"
#include "IE/Modules/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	bool isVideo(std::string path) {
		std::array<std::string, 8> arr{".bmp", ".png", ".jpg", ".tga", ".dds", ".psd", ".hdr", ".pic"};
		std::string str{path.begin() + path.rfind('.'), path.end()};
		return std::count(arr.begin(), arr.end(), str) == 0;
	}
	
	bool videoConvert(const YAML::Node& node, OnlyDrawable*& video) {
#ifdef IE_ImageMagick_FOUND
		if(!node["offset"] && isVideo(node["path"].as<std::string>())) {
			video = new VideoFromFile{
				*node["path"].as<std::vector<sf::Texture>*>(),
				Buffer::get<SCoefficientValue>(node["viewing-progress"])
			};
		} else {
#endif
		video = new VideoFromTexture{
			*node["path"].as<sf::Texture*>(),
			Buffer::get<SCoefficientValue>(node["viewing-progress"]),
			convDef(node["rect"], sf::IntRect{0, 0, 0, 0}),
			convDef(node["count-frame"], 0u),
			convDef(node["offset"], sf::Vector2i{0, 0}),
		};
#ifdef IE_ImageMagick_FOUND
		}
#endif
		return true;
	}
}