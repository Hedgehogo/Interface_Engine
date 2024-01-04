#pragma once

#include <SFML/System.hpp>

namespace ie {
	std::u32string to_utf32(std::string const& str);
	
	sf::String to_utf32(std::u32string const& str);
}
