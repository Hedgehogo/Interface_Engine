#include "Capsule.hpp"

namespace ie {
	Capsule::Make::Make(sf::Color color) : color(color) {
	}
	
	auto Capsule::Make::make(InitInfo init_info) -> Capsule* {
		return new Capsule{std::move(*this), init_info};
	}
	
	Capsule::Capsule(Make&& make, InitInfo init_info) : OnlyDrawable(init_info) {
		rectangle_.setFillColor(make.color);
		circle_.setFillColor(make.color);
	}
	
	Capsule::Capsule(sf::Color color) {
		rectangle_.setFillColor(color);
		circle_.setFillColor(color);
	}
	
	auto Capsule::draw() -> void {
		render_target_->draw(rectangle_);
		circle_.setPosition(layout_.position);
		render_target_->draw(circle_);
		if(layout_.size.x > layout_.size.y) {
			circle_.setPosition({layout_.position.x + layout_.size.x - layout_.size.y, layout_.position.y});
		} else {
			circle_.setPosition({layout_.position.x, layout_.position.y + layout_.size.y - layout_.size.x});
		}
		render_target_->draw(circle_);
	}
	
	auto Capsule::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		layout_.resize(size, position);
		if(size.x > size.y) {
			rectangle_.setSize({size.x - size.y, size.y});
			rectangle_.setPosition(position + sf::Vector2f{size.y / 2, 0});
			circle_.setRadius(size.y / 2);
		} else {
			rectangle_.setSize({size.x, size.y - size.x});
			rectangle_.setPosition(position + sf::Vector2f{0, size.x / 2});
			circle_.setRadius(size.x / 2);
		}
	}
	
	auto Capsule::get_min_size() const -> sf::Vector2f {
		return {0, 0};
	}
	
	auto Capsule::get_normal_size() const -> sf::Vector2f {
		return {1, 1};
	}
	
	auto Capsule::layout_get_data() -> LayoutData& {
		return layout_;
	}
	
	auto Capsule::layout_get_data() const -> LayoutData const& {
		return layout_;
	}
}

auto ieml::Decode<char, ie::Capsule::Make>::decode(ieml::Node const& node) -> orl::Option<ie::Capsule::Make> {
	for(auto& color: node.as<sf::Color>().ok_or_none()) {
		return {{std::move(color)}};
	}
	return {{node.at("color").except().as<sf::Color>().except()}};
}
