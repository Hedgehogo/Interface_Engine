#pragma once
#include "SFML/Graphics.hpp"
#include "../../simple/interactiveSimple.h"
#include "../indivisible/baseIndivisible.h"
namespace ui {
	class BaseTextBlock{
	protected:
        sf::RenderWindow *window;
		sf::Text text;

        uint lineSpacing;
	public:
        struct Edge{
            int start, end;
        };
        BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, sf::Font &font, int size = 0);
        BaseTextBlock(std::wstring text, sf::Color color, sf::Text::Style style, int size = 0);

        void setTextVariables(uint lineSpacing, int size, sf::Font *font);
        void init(sf::RenderWindow &window);

        virtual std::vector<BaseIndivisible*> divide() = 0;

	};
}
