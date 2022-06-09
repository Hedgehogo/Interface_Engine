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
		Sprite(sf::Sprite &sprite, sf::Vector2f minSize, sf::Texture &texture, sf::IntRect rect);
		
		Sprite(sf::Sprite &sprite, sf::Vector2f minSize, sf::Texture &texture);
		
		void draw() override;
		
		void resize(sf::Vector2f size, sf::Vector2f position) override;
		
		sf::Vector2f getMinSize() override;
		
		sf::Vector2f getNormalSize() override;
	};
}
