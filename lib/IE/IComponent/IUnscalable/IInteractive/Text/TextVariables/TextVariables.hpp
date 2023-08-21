#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

using uint = unsigned;

namespace ui {
	struct TextVariables {
		sf::Color TextColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor;
		sf::Font* font;
		sf::Text::Style style;
		uint size;
		float fontLineSpace;
		
		TextVariables(
			sf::Color textColor = sf::Color{}, sf::Color textSelectionColor = sf::Color{}, sf::Color backgroundSelectionColor = sf::Color{},
			sf::Color inactiveTextSelectionColor = sf::Color{}, sf::Color inactiveBackgroundSelectionColor = sf::Color{},
			sf::Font* font = nullptr, sf::Text::Style style = {}, uint size = 0
		);
	};
}