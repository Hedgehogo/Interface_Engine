#pragma once
#include "../iDrawn.h"

namespace ui {
	class RoundedRectangle : public IDrawn {
	protected:
		sf::RectangleShape horizontalRectangle;
		sf::RectangleShape verticalRectangle;
		sf::CircleShape circle;
		sf::Vector2f position;
		sf::Vector2f size;
		float radius;
		
	public:
		RoundedRectangle(sf::Color color, float radius);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		RoundedRectangle* copy() override;
	};
}
