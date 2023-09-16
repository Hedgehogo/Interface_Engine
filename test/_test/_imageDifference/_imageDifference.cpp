#include "_imageDifference.hpp"
#include <algorithm>

sf::Image imageDifference(const sf::Image& first, const sf::Image& second) {
	if(first.getSize() == second.getSize()) {
		sf::Image result;
		result.create(first.getSize().x, first.getSize().y, sf::Color::Transparent);
		for(std::size_t x = 0; x < first.getSize().x; ++x) {
			for(std::size_t y = 0; y < first.getSize().y; ++y) {
				auto firstColor{first.getPixel(x, y)};
				auto secondColor{second.getPixel(x, y)};
				long firstR{firstColor.r},
					firstG{firstColor.g},
					firstB{firstColor.b},
					firstA{firstColor.a},
					secondR{secondColor.r},
					secondG{secondColor.g},
					secondB{secondColor.b},
					secondA{secondColor.a};
				
				result.setPixel(
					x, y,
					sf::Color{
						static_cast<sf::Uint8>(std::abs(firstR - secondR)),
						static_cast<sf::Uint8>(std::abs(firstG - secondG)),
						static_cast<sf::Uint8>(std::abs(firstB - secondB)),
						static_cast<sf::Uint8>(std::abs(firstA - secondA))
					}
				);
			}
		}
		return result;
	}
	return first;
}
