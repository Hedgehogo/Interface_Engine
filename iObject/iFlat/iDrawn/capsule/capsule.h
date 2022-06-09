#pragma once
#include "../iDrawn.h"

namespace ui {
	class Capsule : public IDrawn {
	protected:
		sf::RectangleShape rectangle;
		sf::CircleShape circle;
		sf::Vector2f position;
		sf::Vector2f size;
		
	public:
		Capsule(sf::Color color);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
