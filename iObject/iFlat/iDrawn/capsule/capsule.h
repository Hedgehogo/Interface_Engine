#pragma once
#include "../iDrawn.h"
#include "../../../layout/layout.h"

namespace ui {
	class Capsule : public IDrawn, public Layout {
	protected:
		sf::RectangleShape rectangle;
		sf::CircleShape circle;
		
	public:
		Capsule(sf::Color color);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Capsule* copy() override;
	};
}
