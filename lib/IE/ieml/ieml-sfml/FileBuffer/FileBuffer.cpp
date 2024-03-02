#include "FileBuffer.hpp"

#include <fstream>
#include <localisation/system.hpp>
#include "config.h"

#ifdef IE_ImageMagick_FOUND
#define MAGICKCORE_QUANTUM_DEPTH 16
#define MAGICKCORE_HDRI_ENABLE MAGICKCORE_HDRI_ENABLE_OBSOLETE_IN_H
#include <Magick++.h>
#endif

namespace ie {
	#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	auto LoadFromFile<std::vector<sf::Texture> >::load(std::vector<sf::Texture>& object, std::string name) -> void {
		std::list<Magick::Image> images;
		Magick::read_images(&images, name);
		
		object.resize(images.size());
		
		sf::Vector2<size_t> size_video{images.begin()->base_columns(), images.begin()->base_rows()};
		
		size_t i = 0;
		for(auto& frame: images) {
			frame.magick("RGBA");
			frame.background_color(Magick::Color("transparent"));
			frame.extent({static_cast<size_t>(size_video.x), static_cast<size_t>(size_video.y)}, Magick::CenterGravity);
			
			sf::Image sf_image;
			sf_image.create(size_video.x, size_video.y);
			for(size_t x = 0; x < size_video.x; ++x) {
				for(size_t y = 0; y < size_video.y; ++y) {
					Magick::Color pixel = frame.pixel_color(x, y);
					sf_image.set_pixel(x, y, {
										   static_cast<sf::Uint8>(QuantumScale * pixel.quantum_red() * 255),
										   static_cast<sf::Uint8>(QuantumScale * pixel.quantum_green() * 255),
										   static_cast<sf::Uint8>(QuantumScale * pixel.quantum_blue() * 255),
										   static_cast<sf::Uint8>(QuantumScale * pixel.quantum_alpha() * 255),
									   }
					);
				}
			}
			object[i].load_from_image(sf_image);
			++i;
		}
	}
	*/
	#endif
}

namespace ieml {
	auto Decode<char, sf::Texture&>::decode(ieml::Node const& node) -> orl::Option<sf::Texture&> {
		return {ie::FileBuffer<sf::Texture>::get(node.get_string().except())};
	}
	
	auto Decode<char, sf::Font&>::decode(ieml::Node const& node) -> orl::Option<sf::Font&> {
		return {ie::FileBuffer<sf::Font>::get(node.get_string().except())};
	}
	
	#ifdef IE_ImageMagick_FOUND
	/*old_yaml
	auto Decode<char, std::vector<sf::Texture>&>::decode(ieml::Node const& node) -> orl::Option<std::vector<sf::Texture>&> {
		return {FileBuffer<std::vector<sf::Texture> >::get(node.get_string().except())};
	}
	*/
	#endif
}