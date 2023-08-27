#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ui {
	sf::Color hsvToRgb(float H, float S = 1, float V = 1);
}