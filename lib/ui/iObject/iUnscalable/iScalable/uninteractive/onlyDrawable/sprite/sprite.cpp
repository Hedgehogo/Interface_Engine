#include "sprite.hpp"
#include <algorithm>

namespace ui {
	Sprite::Sprite(sf::Texture &texture, sf::IntRect rect, sf::Vector2f minSize) :
            OnlyDrawable(), sprite(texture, rect), minimumSize(std::max(minSize.x, 1.f), std::max(minSize.y, 1.f)) {
		sprite.setTextureRect(rect);
	}
	
	Sprite::Sprite(sf::Texture &texture, sf::Vector2f minSize) :
            OnlyDrawable(), sprite(texture), minimumSize(std::max(minSize.x, 1.f), std::max(minSize.y, 1.f)) {
	}

	void Sprite::draw() {
		renderTarget->draw(sprite);
	}

	void Sprite::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::FloatRect globalBounds = sprite.getGlobalBounds();
		sprite.scale(sf::Vector2f(size.x / globalBounds.width, size.y / globalBounds.height));
		sprite.setPosition(position);
	}
	
	sf::Vector2f Sprite::getAreaPosition() {
		return sprite.getPosition();
	}
	
	sf::Vector2f Sprite::getAreaSize() {
		return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
	}

	sf::Vector2f Sprite::getMinSize() {
		return minimumSize;
	}
	
	sf::Vector2f Sprite::getNormalSize(){
		return {static_cast<float>(sprite.getTextureRect().width), static_cast<float>(sprite.getTextureRect().height)};
	}
	
	Sprite::Sprite(sf::Sprite sprite, sf::Vector2f minSize) : sprite(sprite), minimumSize(minSize) {}
	
	Sprite *Sprite::copy() {
		Sprite* sprite1 {new Sprite{sprite, minimumSize}};
        OnlyDrawable::copy(sprite1);
		return sprite1;
	}
	
	bool convertPointer(const YAML::Node &node, Sprite *&sprite) {
		sf::Texture* texture;
		sf::Vector2f minSize{};
		
		node["texture"] >> texture;
		if(node["min-size"]) node["min-size"] >> minSize;
		if(node["rect"]) {
			sf::IntRect rect;
			node["rect"] >> rect;
			{ sprite = new Sprite{*texture, rect, minSize}; return true; }
		}
		{ sprite = new Sprite{*texture, minSize}; return true; }
	}
}