#pragma once
#include "../iTextBlock.h"
namespace ui {
	class BaseTextBlock : public ITextBlock {
		sf::RenderWindow *window;
	public:
		struct Edge{
			int start, end;
		};
		void init(sf::RenderWindow &window);
		BaseTextBlock(std::wstring text, sf::Font &font, int size, sf::Color color, sf::Text::Style style);
		sf::Vector2f drawn(sf::Vector2f startDrawn, Edge edge, int lineSpacing);
		ui::IInteraction *getInteraction()override;
	};
}