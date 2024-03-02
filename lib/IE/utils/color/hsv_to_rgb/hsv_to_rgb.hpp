#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ie {
	auto hsv_to_rgb(float H, float S = 1, float V = 1) -> sf::Color;
}