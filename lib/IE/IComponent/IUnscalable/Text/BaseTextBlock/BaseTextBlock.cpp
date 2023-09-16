#include "BaseTextBlock.hpp"

namespace ie {
	BaseTextBlock::BaseTextBlock() {
	}
	
	BaseTextBlock::BaseTextBlock(TextVariables textVariables) : textVariables(textVariables) {
	}
	
	void BaseTextBlock::setTextVariables(
		sf::Color TextColor,
		sf::Color textSelectionColor,
		sf::Color backgroundSelectionColor,
		sf::Color inactiveTextSelectionColor,
		sf::Color inactiveBackgroundSelectionColor,
		sf::Font* font,
		uint size,
		sf::Text::Style style
	) {
		if(!textVariables.TextColor)
			textVariables.TextColor = TextColor;
		if(!textVariables.textSelectionColor)
			textVariables.textSelectionColor = textSelectionColor;
		if(!textVariables.backgroundSelectionColor)
			textVariables.backgroundSelectionColor = backgroundSelectionColor;
		if(!textVariables.inactiveTextSelectionColor)
			textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
		if(!textVariables.inactiveBackgroundSelectionColor)
			textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
		if(!textVariables.font)
			textVariables.font = font;
		if(!textVariables.size)
			textVariables.size = size;
		if(!textVariables.style)
			textVariables.style = style;
	}
}
