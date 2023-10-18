#include "Sprite.hpp"
#include <algorithm>
#include "IE/modules/yaml-cpp/yaml-builder/determine/determine.hpp"

namespace ie {
	Sprite::Make::Make(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size) :
		texture(texture), rect(rect), min_size(min_size) {
	}
	
	Sprite::Make::Make(sf::Texture& texture, sf::Vector2f min_size) :
		texture(texture), rect({}, sf::Vector2i{texture.getSize()}), min_size(min_size) {
	}
	
	Sprite* Sprite::Make::make(InitInfo init_info) {
		return new Sprite{std::move(*this), init_info};
	}
	
	Sprite::Sprite(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		sprite(make.texture, make.rect),
		minimum_size(std::max(make.min_size.x, 1.f), std::max(make.min_size.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size) :
		sprite(texture, rect), minimum_size(std::max(min_size.x, 1.f), std::max(min_size.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::Vector2f min_size) :
		sprite(texture), minimum_size(std::max(min_size.x, 1.f), std::max(min_size.y, 1.f)) {
	}
	
	void Sprite::draw() {
		render_target->draw(sprite);
	}
	
	void Sprite::resize(sf::Vector2f size, sf::Vector2f position) {
		sf::FloatRect global_bounds = sprite.getGlobalBounds();
		sprite.scale(sf::Vector2f(size.x / global_bounds.width, size.y / global_bounds.height));
		sprite.setPosition(position);
	}
	
	sf::Vector2f Sprite::get_area_position() const {
		return sprite.getPosition();
	}
	
	sf::Vector2f Sprite::get_area_size() const {
		return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
	}
	
	sf::Vector2f Sprite::get_min_size() const {
		return minimum_size;
	}
	
	sf::Vector2f Sprite::get_normal_size() const {
		return {static_cast<float>(sprite.getTextureRect().width), static_cast<float>(sprite.getTextureRect().height)};
	}
	
	Sprite* Sprite::copy() {
		return new Sprite{*this};
	}
	
	bool DecodePointer<Sprite>::decode_pointer(const YAML::Node& node, Sprite*& sprite) {
		if(node["rect"]) {
			sprite = new Sprite{
				*node["texture"].as<sf::Texture*>(),
				node["rect"].as<sf::IntRect>(),
				conv_def(node["min-size"], sf::Vector2f{})
			};
		} else {
			sprite = new Sprite{
				*node["texture"].as<sf::Texture*>(),
				conv_def(node["min-size"], sf::Vector2f{})
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