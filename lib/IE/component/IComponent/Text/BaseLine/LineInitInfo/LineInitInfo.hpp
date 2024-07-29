#pragma once

#include <SFML/Graphics.hpp>

namespace ie {
	struct LineInitInfo {
		size_t size;
		sf::Font& font;
		sf::Color color;
		
		LineInitInfo(size_t size, sf::Font& font, sf::Color const& color);
	};
}
