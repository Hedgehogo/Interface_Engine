#include "BaseTextBlock.hpp"

namespace ui {
	BaseTextBlock::BaseTextBlock() {
	}
	
	BaseTextBlock::BaseTextBlock(TextVariables textVariables) : textVariables(textVariables) {
	}
	
	void BaseTextBlock::setTextVariables(sf::Color TextColor, sf::Color textSelectionColor, sf::Color backgroundSelectionColor, sf::Color inactiveTextSelectionColor, sf::Color inactiveBackgroundSelectionColor, sf::Font* font, uint size) {
		if(textVariables.TextColor == sf::Color(255, 255, 255, 0))
			textVariables.TextColor = TextColor;
		if(textVariables.textSelectionColor == sf::Color(255, 255, 255, 0))
			textVariables.textSelectionColor = textSelectionColor;
		if(textVariables.backgroundSelectionColor == sf::Color(255, 255, 255, 0))
			textVariables.backgroundSelectionColor = backgroundSelectionColor;
		if(textVariables.inactiveTextSelectionColor == sf::Color(255, 255, 255, 0))
			textVariables.inactiveTextSelectionColor = inactiveTextSelectionColor;
		if(textVariables.inactiveBackgroundSelectionColor == sf::Color(255, 255, 255, 0))
			textVariables.inactiveBackgroundSelectionColor = inactiveBackgroundSelectionColor;
		if(textVariables.font == nullptr)
			textVariables.font = font;
		if(textVariables.size == 0)
			textVariables.size = size;
	}
}
