#include "baseTextBlock.h"

void ui::BaseTextBlock::init(sf::RenderWindow &window){
	this->window = &window;
}

ui::BaseTextBlock::BaseTextBlock(std::wstring text, sf::Font &font, int size, sf::Color color, sf::Text::Style style) : ITextBlock(text, font, size, color, style) {}

sf::Vector2f ui::BaseTextBlock::drawn(sf::Vector2f startDrawn, Edge edge, int lineSpacing) {
	text.setPosition(startDrawn);
	return {};
}

ui::IInteraction *ui::BaseTextBlock::getInteraction() {
	return nullptr;
}
