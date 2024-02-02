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
		OnlyDrawable(init_info), radius_(make.radius) {
		horizontal_rectangle_.setFillColor(make.color);
		vertical_rectangle_.setFillColor(make.color);
		circle_.setFillColor(make.color);
		circle_.setRadius(radius_);
	}
	
	RoundedRectangle::RoundedRectangle(sf::Color color, float radius) : radius_(radius) {
		horizontal_rectangle_.setFillColor(color);
		vertical_rectangle_.setFillColor(color);
		circle_.setFillColor(color);
		circle_.setRadius(radius);
	}
	
	void RoundedRectangle::draw() {
		render_target_->draw(horizontal_rectangle_);
		render_target_->draw(vertical_rectangle_);
		circle_.setPosition(layout_.position);
		render_target_->draw(circle_);
		circle_.setPosition(layout_.position.x + layout_.size.x - radius_ * 2, layout_.position.y);
		render_target_->draw(circle_);
		circle_.setPosition(layout_.position.x, layout_.position.y + layout_.size.y - radius_ * 2);
		render_target_->draw(circle_);
		circle_.setPosition(layout_.position.x + layout_.size.x - radius_ * 2, layout_.position.y + layout_.size.y - radius_ * 2);
		render_target_->draw(circle_);
	}
	
	void RoundedRectangle::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		vertical_rectangle_.setSize({size.x - radius_ * 2, size.y});
		vertical_rectangle_.setPosition(position + sf::Vector2f{radius_, 0});
		horizontal_rectangle_.setSize({size.x, size.y - radius_ * 2});
		horizontal_rectangle_.setPosition(position + sf::Vector2f{0, radius_});
	}
	
	sf::Vector2f RoundedRectangle::get_min_size() const {
		return sf::Vector2f(radius_ * 2, radius_ * 2);
	}
	
	sf::Vector2f RoundedRectangle::get_normal_size() const {
		return sf::Vector2f(radius_ * 2, radius_ * 2);
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
