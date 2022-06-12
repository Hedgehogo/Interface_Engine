#pragma once
#include "../baseTextBlock.h"
namespace ui {
	class TextBlock : public BaseTextBlock {
		sf::RenderWindow *window;
	public:
        TextBlock(std::wstring text, sf::Color color, sf::Font &font, sf::Text::Style style = {}, int size = 0);
        TextBlock(std::wstring text, sf::Color color, sf::Text::Style style = {}, int size = 0);
        std::vector<BaseIndivisible*> divide();
	};
}