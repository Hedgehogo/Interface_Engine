#include "_imageEqual.hpp"

bool imageEqual(const sf::Image& first, const sf::Image& second) {
	sf::Vector2u size = first.getSize();
	if(size != second.getSize()) {
		return false;
	}
	bool result = true;
	for(std::size_t x = 0; x < size.x; ++x) {
		for(std::size_t y = 0; y < size.x; ++y) {
			sf::Color first_pixel{first.getPixel(x, y)};
			sf::Color second_pixel{second.getPixel(x, y)};
			if(first_pixel != second_pixel) {
				printf("[%zu, %zu] -> ",  x,  y);
				printf("[%u, %u, %u, %u] ", first_pixel.r, first_pixel.g, first_pixel.b, first_pixel.a);
				printf("[%u, %u, %u, %u]\n", second_pixel.r, second_pixel.g, second_pixel.b, second_pixel.a);
				result = false;
			}
		}
	}
	return result;
}
