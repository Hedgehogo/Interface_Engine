#include "Sprite.hpp"
#include <algorithm>
#include "IE\modules\yaml-cpp\yaml-builder\determine\determine.hpp"

namespace ie {
	Sprite::Make::Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f minSize) :
		texture(texture), rect(rect), minSize(minSize) {
	}
	
	Sprite::Make::Make(sf::Texture& texture, sf::Vector2f minSize) :
		texture(texture), rect({}, sf::Vector2i{texture.getSize()}), minSize(minSize) {
	}
	
	Sprite* Sprite::Make::make(InitInfo initInfo) {
		return new Sprite{std::move(*this), initInfo};
	}
	
	Sprite::Sprite(Make&& make, InitInfo initInfo) :
		OnlyDrawable(initInfo),
		sprite(make.texture, make.rect),
		minimumSize(std::max(make.minSize.x, 1.f), std::max(make.minSize.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f minSize) :
		sprite(texture, rect), minimumSize(std::max(minSize.x, 1.f), std::max(minSize.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::Vector2f minSize) :
		sprite(texture), minimumSize(std::max(minSize.x, 1.f), std::max(minSize.y, 1.f)) {
	}
	
	void Sprite::draw() {
		renderTarget->draw(sprite);
	}
	
	void Sprite::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::FloatRect globalBounds = sprite.getGlobalBounds();
		sprite.scale(sf::Vector2f(size.x / globalBounds.width, size.y / globalBounds.height));
		sprite.setPosition(position);
	}
	
	sf::Vector2f Sprite::getAreaPosition() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f Sprite::getAreaSize() const {
		return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
	}
	
	sf::Vector2f Sprite::getMinSize() const {
		return minimumSize;
	}
	
	sf::Vector2f Sprite::getNormalSize() const {
		return {static_cast<float>(sprite.getTextureRect().width), static_cast<float>(sprite.getTextureRect().height)};
	}
	
	Sprite* Sprite::copy() {
		return new Sprite{*this};
	}
	
	bool DecodePointer<Sprite>::decodePointer(const YAML::Node& node, Sprite*& sprite) {
		if(node["rect"]) {
			sprite = new Sprite{
				*node["texture"].as<sf::Texture*>(),
				node["rect"].as<sf::IntRect>(),
				convDef(node["min-size"], sf::Vector2f{})
			};
		} else {
			sprite = new Sprite{
				*node["texture"].as<sf::Texture*>(),
				convDef(node["min-size"], sf::Vector2f{})
			};
		}
		return true;
	}
	
	template<>
	bool determine<Sprite>(const YAML::Node& node) {
		return determine(node, {{"texture"}}, {
			{"rect"},
			{"min-size"}
		});
	}
}