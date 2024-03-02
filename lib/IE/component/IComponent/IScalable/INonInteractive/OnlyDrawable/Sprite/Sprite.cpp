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
	
	auto Sprite::Make::make(InitInfo init_info) -> Sprite* {
		return new Sprite{std::move(*this), init_info};
	}
	
	Sprite::Sprite(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info),
		sprite_(make.texture, make.rect),
		minimum_size_(std::max(make.min_size.x, 1.f), std::max(make.min_size.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::IntRect rect, sf::Vector2f min_size) :
		sprite_(texture, rect), minimum_size_(std::max(min_size.x, 1.f), std::max(min_size.y, 1.f)) {
	}
	
	Sprite::Sprite(sf::Texture& texture, sf::Vector2f min_size) :
		sprite_(texture), minimum_size_(std::max(min_size.x, 1.f), std::max(min_size.y, 1.f)) {
	}
	
	auto Sprite::draw() -> void {
		render_target_->draw(sprite_);
	}
	
	auto Sprite::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		auto global_bounds{sprite_.getGlobalBounds()};
		sprite_.scale(sf::Vector2f(size.x / global_bounds.width, size.y / global_bounds.height));
		sprite_.setPosition(position);
	}
	
	auto Sprite::get_area_position() const -> sf::Vector2f {
		return sprite_.getPosition();
	}
	
	auto Sprite::get_area_size() const -> sf::Vector2f {
		return {sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height};
	}
	
	auto Sprite::get_min_size() const -> sf::Vector2f {
		return minimum_size_;
	}
	
	auto Sprite::get_normal_size() const -> sf::Vector2f {
		return {static_cast<float>(sprite_.getTextureRect().width), static_cast<float>(sprite_.getTextureRect().height)};
	}
	
	auto Determine<Sprite::Make>::determine(ieml::Node const& node) -> bool {
		return ie::determine(node, {{"texture"}}, {
			{"rect"},
			{"min-size"}
		});
	}
}

auto ieml::Decode<char, ie::Sprite::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Sprite::Make> {
	auto map{node.get_map_view().except()};
	auto& texture{map.at("texture").except().as<sf::Texture&>().except()};
	auto min_size{map.get_as<sf::Vector2f>("min-size").except().ok_or({})};
	for(auto& rect: map.at("rect").ok_or_none()) {
		return {{texture, rect.as<sf::IntRect>().except(), min_size}};
	}
	return {{texture, min_size}};
}
