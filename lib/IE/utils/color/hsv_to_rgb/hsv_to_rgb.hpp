#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ie {
	sf::Color hsv_to_rgb(float H, float S = 1, float V = 1);
}