#include "FullColor.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"
#include "IE/ieml/determine/determine.hpp"

namespace ie {
	FullColor::Make::Make(sf::Color color, sf::Vector2f normal_size) : color(color), normal_size(normal_size) {
	}
	
	FullColor* FullColor::Make::make(InitInfo init_info) {
		return new FullColor{std::move(*this), init_info};
	}
	
	FullColor::FullColor(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info), normal_size_(make.normal_size) {
		rectangle_.setFillColor(make.color);
	}
	
	FullColor::FullColor(sf::Color color, sf::Vector2f normal_size) : OnlyDrawable(), rectangle_(), normal_size_(normal_size) {
		rectangle_.setFillColor(color);
	}
	
	void FullColor::draw() {
		render_target_->draw(rectangle_);
	}
	
	void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
		rectangle_.setSize(size);
		rectangle_.setPosition(position);
	}
	
	sf::Vector2f FullColor::get_area_position() const {
		return rectangle_.getPosition();
	}
	
	sf::Vector2f FullColor::get_area_size() const {
		return rectangle_.getSize();
	}
	
	sf::Vector2f FullColor::get_min_size() const {
		return {};
	}
	
	sf::Vector2f FullColor::get_normal_size() const {
		return normal_size_;
	}
	
	bool Determine<FullColor::Make>::determine(const ieml::Node& node) {
		for(auto& str: node.get_raw().ok_or_none()) {
			return str.str.size() <= 11;
		}
		return ie::determine(node, {{"color", ieml::NodeType::Raw}}, {{"normal-size"}});
	}
}

orl::Option<ie::FullColor::Make> ieml::Decode<char, ie::FullColor::Make>::decode(ieml::Node const& node) {
	for(auto& color: node.as<sf::Color>().ok_or_none()) {
		return ie::FullColor::Make{color};
	}
	auto map{node.get_map_view().except()};
	return ie::FullColor::Make{
		map.at("color").except().as<sf::Color>().except(),
		map.get_as<sf::Vector2f>("normal-size").ok_or({})
	};
}
