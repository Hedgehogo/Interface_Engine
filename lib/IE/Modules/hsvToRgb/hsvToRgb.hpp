#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ie {
	sf::Color hsvToRgb(float H, float S = 1, float V = 1);
}