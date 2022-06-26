#include "sprite.h"
#include <algorithm>
#include <SFML/Graphics.hpp>


namespace ui {
	Sprite::Sprite(sf::Texture &texture, sf::IntRect rect, sf::Vector2f minSize) :
		IDrawn(), sprite(texture, rect), minimumSize(std::max(minimumSize.x, 1.f), std::max(minimumSize.y, 1.f)) {
		sprite.setTextureRect(rect);
	}
	
	Sprite::Sprite(sf::Texture &texture, sf::Vector2f minSize) :
		IDrawn(), sprite(texture), minimumSize(std::max(minimumSize.x, 1.f), std::max(minimumSize.y, 1.f)) {
	}

	void Sprite::draw() {
		renderTarget->draw(sprite);
	}

	void Sprite::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::FloatRect globalBounds = sprite.getGlobalBounds();
		sprite.scale(sf::Vector2f(size.x / globalBounds.width, size.y / globalBounds.height));
		sprite.setPosition(position);
	}
	
	sf::Vector2f Sprite::getPosition() {
		return sprite.getPosition();
	}
	
	sf::Vector2f Sprite::getSize() {
		return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
	}

	sf::Vector2f Sprite::getMinSize() {
		return minimumSize;
	}
	
	sf::Vector2f Sprite::getNormalSize(){
		return {static_cast<float>(sprite.getTextureRect().width),static_cast<float>(sprite.getTextureRect().height)};
	}
	
	Sprite::Sprite(sf::Sprite sprite, sf::Vector2f minSize) : sprite(sprite), minimumSize(minSize) {}
	
	Sprite *Sprite::copy() {
		Sprite* sprite1 {new Sprite{sprite, minimumSize}};
		IDrawn::copy(sprite1);
		return sprite1;
	}
}