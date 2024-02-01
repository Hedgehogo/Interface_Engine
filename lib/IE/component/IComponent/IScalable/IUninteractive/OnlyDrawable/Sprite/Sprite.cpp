#include "Sprite.hpp"
#include <algorithm>
#include "IE/ieml/ieml-sfml/FileBuffer/FileBuffer.hpp"
#include "IE/ieml/determine/determine.hpp"

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
	
	bool Determine<Sprite::Make>::determine(ieml::Node const& node) {
		return ie::determine(node, {{"texture"}}, {
			{"rect"},
			{"min-size"}
		});
	}
}

orl::Option<ie::Sprite::Make> ieml::Decode<char, ie::Sprite::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	auto& texture{map.at("texture").except().as<sf::Texture&>().except()};
	auto min_size{map.get_as<sf::Vector2f>("min-size").ok_or({})};
	if(auto rect{map.at("rect")}) {
		return ie::Sprite::Make{texture, rect.ok().as<sf::IntRect>().except(), min_size};
	}
	return ie::Sprite::Make{texture, min_size};
}
