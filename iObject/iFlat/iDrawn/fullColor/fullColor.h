#pragma once
#include <SFML/Graphics.hpp>

#include "../iDrawn.h"

namespace ui {
    class FullColor : public IDrawn {
	protected:
		sf::RectangleShape rectangle;
		sf::Vector2f normalSize;

	public:
		explicit FullColor(sf::Color color, sf::Vector2f normalSize = {0, 0});
	
		void draw() override;
	
		void resize(sf::Vector2f size, sf::Vector2f position) override;
	
		sf::Vector2f getMinSize() override;
	
		sf::Vector2f getNormalSize() override;
	};
}

