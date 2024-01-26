#include "Capsule.hpp"

namespace ie {
	Capsule::Make::Make(sf::Color color) : color(color) {
	}
	
	Capsule* Capsule::Make::make(InitInfo init_info) {
		return new Capsule{std::move(*this), init_info};
	}
	
	Capsule::Capsule(Make&& make, InitInfo init_info) : OnlyDrawable(init_info) {
		rectangle.setFillColor(make.color);
		circle.setFillColor(make.color);
	}
	
	Capsule::Capsule(sf::Color color) {
		rectangle.setFillColor(color);
		circle.setFillColor(color);
	}
	
	void Capsule::draw() {
		render_target->draw(rectangle);
		circle.setPosition(layout_.position);
		render_target->draw(circle);
		if(layout_.size.x > layout_.size.y) {
			circle.setPosition({layout_.position.x + layout_.size.x - layout_.size.y, layout_.position.y});
		} else {
			circle.setPosition({layout_.position.x, layout_.position.y + layout_.size.y - layout_.size.x});
		}
		render_target->draw(circle);
	}
	
	void Capsule::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		if(size.x > size.y) {
			rectangle.setSize({size.x - size.y, size.y});
			rectangle.setPosition(position + sf::Vector2f{size.y / 2, 0});
			circle.setRadius(size.y / 2);
		} else {
			rectangle.setSize({size.x, size.y - size.x});
			rectangle.setPosition(position + sf::Vector2f{0, size.x / 2});
			circle.setRadius(size.x / 2);
		}
	}
	
	sf::Vector2f Capsule::get_min_size() const {
		return {0, 0};
	}
	
	sf::Vector2f Capsule::get_normal_size() const {
		return {1, 1};
	}
	
	Capsule* Capsule::copy() {
		return new Capsule{*this};
	}
	
	LayoutData& Capsule::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& Capsule::layout_get_data() const {
		return layout_;
	}
}

orl::Option<ie::Capsule::Make> ieml::Decode<char, ie::Capsule::Make>::decode(ieml::Node const& node) {
	return {{node.at("color").except().as<sf::Color>().except()}};
}
