#include "FileBuffer.hpp"

#include <fstream>
#include <localisation/system.hpp>

namespace ieml {
	auto Decode<char, sf::Texture&>::decode(ieml::Node const& node) -> orl::Option<sf::Texture&> {
		return {ie::FileBuffer<sf::Texture>::get(node.get_string().except())};
	}
	
	auto Decode<char, sf::Font&>::decode(ieml::Node const& node) -> orl::Option<sf::Font&> {
		return {ie::FileBuffer<sf::Font>::get(node.get_string().except())};
	}
}