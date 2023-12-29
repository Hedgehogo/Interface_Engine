#include "TextVariables.hpp"

namespace ie {
	TextVariables::TextVariables(
		orl::Option<sf::Color> text_color,
		orl::Option<sf::Color> text_selection_color,
		orl::Option<sf::Color> background_selection_color,
		orl::Option<sf::Color> inactive_text_selection_color,
		orl::Option<sf::Color> inactive_background_selection_color,
		orl::Option<sf::Font*> font,
		orl::Option<sf::Text::Style> style,
		orl::Option<size_t> size
	) :
		text_color(text_color),
		text_selection_color(text_selection_color),
		background_selection_color(background_selection_color),
		inactive_text_selection_color(inactive_text_selection_color),
		inactive_background_selection_color(inactive_background_selection_color),
		size(size),
		font(font),
		font_line_space(font && size ? orl::Option{font.some()->getLineSpacing(this->size.some())} : orl::Option<float>{}),
		style(style) {
	}
}