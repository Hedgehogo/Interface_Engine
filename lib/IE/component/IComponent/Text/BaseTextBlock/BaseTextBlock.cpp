#include "BaseTextBlock.hpp"

namespace ie {
	BaseTextBlock::BaseTextBlock(TextVariables text_variables) : text_variables_(text_variables) {
	}
	
	auto BaseTextBlock::set_kerning(char32_t) -> void {
	}
	
	auto BaseTextBlock::set_text_variables(
		sf::Color text_color,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Font& font,
		size_t size,
		sf::Text::Style style
	) -> void {
		if(!text_variables_.text_color.is_some())
			text_variables_.text_color = text_color;
		if(!text_variables_.text_selection_color.is_some())
			text_variables_.text_selection_color = text_selection_color;
		if(!text_variables_.background_selection_color.is_some())
			text_variables_.background_selection_color = background_selection_color;
		if(!text_variables_.inactive_text_selection_color.is_some())
			text_variables_.inactive_text_selection_color = inactive_text_selection_color;
		if(!text_variables_.inactive_background_selection_color.is_some())
			text_variables_.inactive_background_selection_color = inactive_background_selection_color;
		if(!text_variables_.font.is_some())
			text_variables_.font = font;
		if(!text_variables_.size.is_some())
			text_variables_.size = size;
		if(!text_variables_.style.is_some())
			text_variables_.style = style;
	}
}
