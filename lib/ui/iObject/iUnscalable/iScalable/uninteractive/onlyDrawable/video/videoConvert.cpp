#include "videoConvert.hpp"
#include "videoFromFile/videoFromFile.hpp"
#include "videoFromTexture/videoFromTexture.hpp"
#include "modules/appendix/yaml-cpp/fileBuffer/fileBuffer.hpp"

namespace ui {
	bool isVideo(std::string path){
		std::array<std::string, 8> arr{".bmp", ".png", ".jpg", ".tga", ".dds", ".psd", ".hdr", ".pic"};
		std::string str{path.begin() + path.rfind('.'), path.end()};
		return std::count(arr.begin(), arr.end(), str) == 0;
	}

	bool videoConvert(const YAML::Node &node, OnlyDrawable *&video) {
		if (std::string path{node["path"].as<std::string>()};!node["offset"] && isVideo(path)){
			video = new VideoFromFile{
				path,
				Buffer::get<SCoefficientValue>(node["viewing-progress"]),
				convDef(node["rect"], sf::IntRect{0, 0, 0, 0})
			};
		} else{
			video = new VideoFromTexture{
				*node["path"].as<sf::Texture *>(),
				Buffer::get<SCoefficientValue>(node["viewing-progress"]),
				convDef(node["rect"], sf::IntRect{0, 0, 0, 0}),
				convDef(node["count-frame"], 0),
				convDef(node["offset"], sf::Vector2i{0, 0}),
			};
		}

		return true;
	}
}