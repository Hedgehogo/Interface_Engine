#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ui{
	sf::Color HSVtoRGB(float H, float S = 1, float V = 1);
}