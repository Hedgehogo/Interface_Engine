#include "sprite.h"
#include <SFML/Graphics.hpp>


namespace ui {
	Sprite::Sprite(sf::Sprite& sprite, sf::Vector2f minSize, sf::Texture& texture, sf::IntRect rect) :
		IDrawn(), sprite(sprite), minimumSize(minSize), texture(texture), rect(rect) {}
	
	Sprite::Sprite(sf::Sprite& sprite, sf::Vector2f minSize, sf::Texture& texture) :
		IDrawn(), sprite(sprite), minimumSize(minSize), texture(texture), rect(sf::Vector2i(0, 0), static_cast<sf::Vector2i>(texture.getSize())) {}

	void Sprite::draw() {
		sprite.setTexture(texture);
		if (rect.height != 0 || rect.width != 0)
			sprite.setTextureRect(rect);
		sprite.setScale(scale);
		sprite.setPosition(position);
		window->draw(sprite);
	}

	void Sprite::resize(sf::Vector2f size, sf::Vector2f position) {
		scale = sf::Vector2f(size.x / static_cast<float>(texture.getSize().x), size.y / static_cast<float>(texture.getSize().y));
		this->position = position;
	}

	sf::Vector2f Sprite::getMinSize() {
		return minimumSize;
	}
	
	sf::Vector2f Sprite::getNormalSize(){
		return {static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)};
	}
}