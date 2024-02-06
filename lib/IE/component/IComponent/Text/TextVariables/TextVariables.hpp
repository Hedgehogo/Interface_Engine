#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <optional>
#include <option_result/option_result.hpp>

namespace ie {
	struct TextVariables {
		orl::Option<sf::Color> text_color, text_selection_color, background_selection_color, inactive_text_selection_color, inactive_background_selection_color;
		orl::Option<size_t> size;
		orl::Option<sf::Font&> font;
		orl::Option<float> font_line_space;
		orl::Option<sf::Text::Style> style;
		
		TextVariables(
			orl::Option<sf::Color> text_color = {},
			orl::Option<sf::Color> text_selection_color = {},
			orl::Option<sf::Color> background_selection_color = {},
			orl::Option<sf::Color> inactive_text_selection_color = {},
			orl::Option<sf::Color> inactive_background_selection_color = {},
			orl::Option<sf::Font&> font = {},
			orl::Option<sf::Text::Style> style = {},
			orl::Option<size_t> size = {}
		);
	};
}