#pragma once
#include <SFML/Graphics.hpp>
#include "../iDrawn.h"

namespace ui {
	class Sprite : public IDrawn {
	protected:
		sf::Vector2f minimumSize;
		
		//render
		sf::Sprite &sprite;
		sf::Texture &texture;
		sf::IntRect rect;
		sf::Vector2f scale;
		sf::Vector2f position;
	
	public:
		Sprite(sf::Sprite &sprite, sf::Texture &texture, sf::IntRect rect, sf::Vector2f minSize);
		
		Sprite(sf::Sprite &sprite, sf::Texture &texture, sf::Vector2f minSize);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
		
		Sprite* copy() override;
	};
}
