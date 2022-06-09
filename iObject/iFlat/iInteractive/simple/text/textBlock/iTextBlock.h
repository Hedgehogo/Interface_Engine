#pragma once
#include "SFML/Graphics.hpp"
#include "../../../iInteractive.h"

namespace ui {
	class ITextBlock {
	protected:
		sf::Text text;
	public:
		ITextBlock(std::wstring text, sf::Font &font, int size, sf::Color color, sf::Text::Style style);
		virtual sf::Vector2f drawn(sf::Vector2f startDrawn) = 0;
		virtual ui::IInteraction *getInteraction() = 0;
	};
}
