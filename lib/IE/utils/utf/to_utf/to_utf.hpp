#pragma once

#include <SFML/System.hpp>

namespace ie {
	auto to_utf32(std::string_view str) -> std::u32string;
	
	auto to_utf32(std::u32string_view str) -> sf::String;
}
