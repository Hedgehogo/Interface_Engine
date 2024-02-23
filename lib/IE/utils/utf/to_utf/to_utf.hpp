#pragma once

#include <SFML/System.hpp>

namespace ie {
	std::u32string to_utf32(std::string_view str);
	
	sf::String to_utf32(std::u32string_view str);
}
