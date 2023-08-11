#include "_imageEqual.hpp"

bool imageEqual(const sf::Image& first, const sf::Image& second) {
	sf::Vector2u size = first.getSize();
	if(size != second.getSize()) {
		return false;
	}
	
	for(std::size_t x = 0; x < size.x; ++x) {
		for(std::size_t y = 0; y < size.x; ++y) {
			sf::Color first_pixel{first.getPixel(x, y)};
			sf::Color second_pixel{second.getPixel(x, y)};
			if(first_pixel != second_pixel) {
				return false;
			}
		}
	}
	return true;
}
