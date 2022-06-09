#pragma once
#include "../iDrawn.h"

namespace ui {
	class Empty : public IDrawn {
	public:
		void draw() override;
		
		void resize(sf::Vector2f, sf::Vector2f) override;
		
		bool updateInteractions(sf::Vector2f) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
