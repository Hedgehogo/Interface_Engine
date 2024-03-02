#include "image_difference.hpp"
#include <algorithm>

sf::Image image_difference(const sf::Image& first, const sf::Image& second) {
	if(first.getSize() == second.getSize()) {
		sf::Image result;
		result.create(first.getSize().x, first.getSize().y, sf::Color::Transparent);
		for(size_t x = 0; x < first.getSize().x; ++x) {
			for(size_t y = 0; y < first.getSize().y; ++y) {
				auto first_color{first.getPixel(x, y)};
				auto second_color{second.getPixel(x, y)};
				long first_r{first_color.r},
					first_g{first_color.g},
					first_b{first_color.b},
					first_a{first_color.a},
					second_r{second_color.r},
					second_g{second_color.g},
					second_b{second_color.b},
					second_a{second_color.a};
				
				result.setPixel(
					x, y,
					sf::Color{
						static_cast<sf::Uint8>(std::abs(first_r - second_r)),
						static_cast<sf::Uint8>(std::abs(first_g - second_g)),
						static_cast<sf::Uint8>(std::abs(first_b - second_b)),
						static_cast<sf::Uint8>(std::abs(first_a - second_a))
					}
				);
			}
		}
		return result;
	}
	return first;
}
