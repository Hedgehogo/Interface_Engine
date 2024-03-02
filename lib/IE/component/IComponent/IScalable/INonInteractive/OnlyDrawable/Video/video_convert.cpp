#include "video_convert.hpp"
#include "VideoFromFile/VideoFromFile.hpp"

#ifdef IE_ImageMagick_FOUND
#include "VideoFromFile/VideoFromFile.hpp"
#endif

#include "VideoFromTexture/VideoFromTexture.hpp"
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/ieml/shortcuts/shortcuts.hpp"

namespace ie {
	auto is_video(std::string_view path) -> bool {
		std::array<std::string_view, 8> arr{".bmp", ".png", ".jpg", ".tga", ".dds", ".psd", ".hdr", ".pic"};
		std::string_view str{path.substr(path.rfind('.'))};
		return std::count(arr.begin(), arr.end(), str) == 0;
	}
	
	auto video_convert(ieml::Node const& node) -> orl::Option<OnlyDrawable::Make*> {
		auto map{node.get_map_view().except()};
		auto& path_node{map.at("path").except()};
		auto viewing_progress{map.at("viewing-progress").except().as<MakeDyn<ISRFloat> >().except()};
#ifdef IE_ImageMagick_FOUND
		/*old_yaml
		if(!map.at("offset").is_ok() && is_video(path_node.get_string().except())) {
			return new VideoFromFile::Make{
				path_node.as<std::vector<sf::Texture>&>().except(),
				std::move(viewing_progress)
			};
		}
		*/
#endif
		return new VideoFromTexture::Make{
			path_node.as<sf::Texture&>().except(),
			std::move(viewing_progress),
			map.get_as<sf::IntRect>("rect").except().ok_or({0, 0, 0, 0}),
			map.get_as<size_t>("count-frame").except().ok_or(0u),
			map.get_as<sf::Vector2i>("offset").except().ok_or({0, 0})
		};
	}
}