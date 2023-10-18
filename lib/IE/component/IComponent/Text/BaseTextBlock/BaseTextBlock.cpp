#include "BaseTextBlock.hpp"

namespace ie {
	BaseTextBlock::BaseTextBlock() {
	}
	
	BaseTextBlock::BaseTextBlock(TextVariables text_variables) : text_variables(text_variables) {
	}
	
	void BaseTextBlock::set_kerning(char32_t) {
	}
	
	void BaseTextBlock::set_text_variables(
		sf::Color TextColor,
		sf::Color text_selection_color,
		sf::Color background_selection_color,
		sf::Color inactive_text_selection_color,
		sf::Color inactive_background_selection_color,
		sf::Font* font,
		uint size,
		sf::Text::Style style
	) {
		if(!text_variables.text_color)
			text_variables.text_color = TextColor;
		if(!text_variables.text_selection_color)
			text_variables.text_selection_color = text_selection_color;
		if(!text_variables.background_selection_color)
			text_variables.background_selection_color = background_selection_color;
		if(!text_variables.inactive_text_selection_color)
			text_variables.inactive_text_selection_color = inactive_text_selection_color;
		if(!text_variables.inactive_background_selection_color)
			text_variables.inactive_background_selection_color = inactive_background_selection_color;
		if(!text_variables.font)
			text_variables.font = font;
		if(!text_variables.size)
			text_variables.size = size;
		if(!text_variables.style)
			text_variables.style = style;
	}
}
