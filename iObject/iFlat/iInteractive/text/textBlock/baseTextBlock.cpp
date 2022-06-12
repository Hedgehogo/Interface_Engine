#include "baseTextBlock.h"

ui::BaseTextBlock::BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, sf::Font &font, int size) {
	this->text.setString(text);
	this->text.setFont(font);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setStyle(style);
}

ui::BaseTextBlock::BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, int size) {
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setStyle(style);
}

void ui::BaseTextBlock::init(sf::RenderWindow &window) {
    this->window = &window;
}

void ui::BaseTextBlock::setTextVariables(uint lineSpacing, int size, sf::Font *font) {
    this->lineSpacing = lineSpacing;

    if (text.getCharacterSize() == 0)
        text.setCharacterSize(size);
    if (text.getFont() == nullptr)
        text.setFont(*font);
}