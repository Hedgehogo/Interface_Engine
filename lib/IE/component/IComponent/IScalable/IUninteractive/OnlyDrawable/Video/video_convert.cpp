#include "video_convert.hpp"
#include "VideoFromFile/VideoFromFile.hpp"
#ifdef IE_ImageMagick_FOUND
#include "VideoFromFile/VideoFromFile.hpp"
#endif
#include "VideoFromTexture/VideoFromTexture.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	bool is_video(std::string path) {
		std::array<std::string, 8> arr{".bmp", ".png", ".jpg", ".tga", ".dds", ".psd", ".hdr", ".pic"};
		std::string str{path.begin() + path.rfind('.'), path.end()};
		return std::count(arr.begin(), arr.end(), str) == 0;
	}
	
	orl::Option<OnlyDrawable*> video_convert(ieml::Node const& node) {
		throw std::runtime_error("video_convert() not implemented");
		/*old_yaml
		auto& path_node{node.at("path").except()};
#ifdef IE_ImageMagick_FOUND
		if(!node.at("offset").is_ok() && is_video(path_node.get_string().except())) {
			return new VideoFromFile{
				path_node.as<std::vector<sf::Texture>&>().except(),
				node.at("viewing-progress").except().as<PSCoefficient>().except()
			};
		}
#endif
		return new VideoFromTexture{
			path_node.as<sf::Texture&>().except(),
			node.at("viewing-progress").except().as<PSCoefficient>().except(),
			node.get_as<sf::IntRect>("rect").ok_or({0, 0, 0, 0}),
			node.get_as<size_t>("count-frame").ok_or(0u),
			node.get_as<sf::Vector2i>("offset").ok_or({0, 0})
		};
		*/
	}
}