#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <optional>
#include <option_result/option_result.hpp>

using uint = unsigned;

namespace ie {
	struct TextVariables {
		orl::Option<sf::Color> textColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor;
		orl::Option<uint> size;
		orl::Option<sf::Font*> font;
		orl::Option<float> fontLineSpace;
		orl::Option<sf::Text::Style> style;
		
		TextVariables(
			orl::Option<sf::Color> textColor = {},
			orl::Option<sf::Color> textSelectionColor = {},
			orl::Option<sf::Color> backgroundSelectionColor = {},
			orl::Option<sf::Color> inactiveTextSelectionColor = {},
			orl::Option<sf::Color> inactiveBackgroundSelectionColor = {},
			orl::Option<sf::Font*> font = {},
			orl::Option<sf::Text::Style> style = {},
			orl::Option<uint> size = {}
		);
	};
}