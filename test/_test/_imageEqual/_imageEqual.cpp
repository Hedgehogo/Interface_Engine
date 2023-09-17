#include "_imageEqual.hpp"
#include <algorithm>

float totalDifferenceColor(sf::Color first, sf::Color second) {
	return static_cast<float >(std::abs(static_cast<long>(first.r) - static_cast<long>(second.r)) +
							   std::abs(static_cast<long>(first.g) - static_cast<long>(second.g)) +
							   std::abs(static_cast<long>(first.b) - static_cast<long>(second.b)) +
							   std::abs(static_cast<long>(first.a) - static_cast<long>(second.a)));
}

bool imageEqual(const sf::Image& first, const sf::Image& second, float precision) {
	sf::Vector2u size = first.getSize();
	if(size != second.getSize()) {
		return false;
	}
	float totalDifference{0};
	for(std::size_t x = 0; x < size.x; ++x) {
		for(std::size_t y = 0; y < size.y; ++y) {
			totalDifference += totalDifferenceColor(first.getPixel(x, y), second.getPixel(x, y));
		}
	}
	return (totalDifference / static_cast<float>(size.x * size.y * 4)) <= precision;
}
