#pragma once

#include <SFML/Graphics.hpp>

namespace ie {
	struct LineInitInfo {
		size_t size;
		sf::Font& font;
		sf::Color color;
		sf::RenderTarget& render_target;
		
		LineInitInfo(size_t size, sf::Font& font, sf::Color const& color, sf::RenderTarget& render_target);
	};
}
