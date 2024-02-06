#include "image_equal.hpp"
#include <algorithm>

float total_difference_color(sf::Color first, sf::Color second) {
	return static_cast<float >(std::abs(static_cast<long>(first.r) - static_cast<long>(second.r)) +
							   std::abs(static_cast<long>(first.g) - static_cast<long>(second.g)) +
							   std::abs(static_cast<long>(first.b) - static_cast<long>(second.b)) +
							   std::abs(static_cast<long>(first.a) - static_cast<long>(second.a)));
}

bool image_equal(const sf::Image& first, const sf::Image& second, float precision) {
	sf::Vector2u size = first.getSize();
	if(size != second.getSize()) {
		return false;
	}
	float total_difference{0};
	for(size_t x = 0; x < size.x; ++x) {
		for(size_t y = 0; y < size.y; ++y) {
			total_difference += total_difference_color(first.getPixel(x, y), second.getPixel(x, y));
		}
	}
	return (total_difference / static_cast<float>(size.x * size.y * 4)) <= precision;
}
