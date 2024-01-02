#include "RoundedRectangle.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	RoundedRectangle::Make::Make(sf::Color color, float radius) : color(color), radius(radius) {
	}
	
	RoundedRectangle* RoundedRectangle::Make::make(InitInfo init_info) {
		return new RoundedRectangle{std::move(*this), init_info};
	}
	
	RoundedRectangle::RoundedRectangle(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info), radius(make.radius) {
		horizontal_rectangle.setFillColor(make.color);
		vertical_rectangle.setFillColor(make.color);
		circle.setFillColor(make.color);
		circle.setRadius(radius);
	}
	
	RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius(radius) {
		horizontal_rectangle.setFillColor(color);
		vertical_rectangle.setFillColor(color);
		circle.setFillColor(color);
		circle.setRadius(radius);
	}
	
	void RoundedRectangle::draw() {
		render_target->draw(horizontal_rectangle);
		render_target->draw(vertical_rectangle);
		circle.setPosition(layout_.position);
		render_target->draw(circle);
		circle.setPosition(layout_.position.x + layout_.size.x - radius * 2, layout_.position.y);
		render_target->draw(circle);
		circle.setPosition(layout_.position.x, layout_.position.y + layout_.size.y - radius * 2);
		render_target->draw(circle);
		circle.setPosition(layout_.position.x + layout_.size.x - radius * 2, layout_.position.y + layout_.size.y - radius * 2);
		render_target->draw(circle);
	}
	
	void RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		vertical_rectangle.setSize({size.x - radius * 2, size.y});
		vertical_rectangle.setPosition(position + sf::Vector2f{radius, 0});
		horizontal_rectangle.setSize({size.x, size.y - radius * 2});
		horizontal_rectangle.setPosition(position + sf::Vector2f{0, radius});
	}
	
	sf::Vector2f RoundedRectangle::get_min_size() const {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	sf::Vector2f RoundedRectangle::get_normal_size() const {
		return sf::Vector2f(radius * 2, radius * 2);
	}
	
	RoundedRectangle* RoundedRectangle::copy() {
		return new RoundedRectangle{*this};
	}
	
	LayoutData& RoundedRectangle::layout_get_data() {
		return layout_;
	}
	
	const LayoutData& RoundedRectangle::layout_get_data() const {
		return layout_;
	}
	
	bool Determine<RoundedRectangle::Make>::determine(ieml::Node const& node) {
		return ie::determine(node, {
			{"color",  ieml::NodeType::Raw},
			{"radius", ieml::NodeType::Raw}
		});
	}
}

orl::Option<ie::RoundedRectangle::Make> ieml::Decode<char, ie::RoundedRectangle::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::RoundedRectangle::Make{
		map.at("color").except().as<sf::Color>().except(),
		map.at("radius").except().as<float>().except(),
	};
}
