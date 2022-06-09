#include "iTextBlock.h"

ui::ITextBlock::ITextBlock(std::wstring text, sf::Font &font, int size, sf::Color color, sf::Text::Style style) {
	this->text.setString(text);
	this->text.setFont(font);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setStyle(style);
}