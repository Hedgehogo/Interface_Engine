#pragma once
#include "../iDrawn.h"

namespace ui {
	class Rectangle : public IDrawn {
	protected:
		sf::RectangleShape horizontalRectangle;
		sf::RectangleShape verticalRectangle;
		sf::CircleShape circle;
		sf::Vector2f position;
		sf::Vector2f size;
		float radius;
		
	public:
		Rectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Rectangle* copy() override;
	};
}
