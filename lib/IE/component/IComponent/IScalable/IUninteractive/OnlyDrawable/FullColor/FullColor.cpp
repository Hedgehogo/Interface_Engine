#include "FullColor.hpp"
#include "IE/ieml/ieml-sfml/ieml-sfml.hpp"

namespace ie {
	FullColor::Make::Make(sf::Color color, sf::Vector2f normal_size) : color(color), normal_size(normal_size) {
	}
	
	FullColor* FullColor::Make::make(InitInfo init_info) {
		return new FullColor{std::move(*this), init_info};
	}
	
	FullColor::FullColor(Make&& make, InitInfo init_info) :
		OnlyDrawable(init_info), normal_size(make.normal_size) {
		rectangle.setFillColor(make.color);
	}
	
	FullColor::FullColor(sf::Color color, sf::Vector2f normal_size) : OnlyDrawable(), rectangle(), normal_size(normal_size) {
		rectangle.setFillColor(color);
	}
	
	void FullColor::draw() {
		render_target->draw(rectangle);
	}
	
	void FullColor::resize(sf::Vector2f size, sf::Vector2f position) {
		rectangle.setSize(size);
		rectangle.setPosition(position);
	}
	
	sf::Vector2f FullColor::get_area_position() const {
		return rectangle.getPosition();
	}
	
	sf::Vector2f FullColor::get_area_size() const {
		return rectangle.getSize();
	}
	
	sf::Vector2f FullColor::get_min_size() const {
		return {};
	}
	
	sf::Vector2f FullColor::get_normal_size() const {
		return normal_size;
	}
	
	FullColor* FullColor::copy() {
		return new FullColor{*this};
	}
	
	/*old_yaml_determine_impl
	template<>
	bool determine<FullColor>(const YAML::Node& node) {
		if(node.IsScalar()) {
			return node.as<std::string>().size() <= 11;
		} else {
			return determine(node, {{"color", YAML::NodeType::Scalar}}, {{"normal-size"}});
		}
	}
	*/
}

orl::Option<ie::FullColor> ieml::Decode<char, ie::FullColor>::decode(ieml::Node const& node) {
	if(auto color{node.as<sf::Color>()}) {
		return ie::FullColor{color.ok()};
	} else {
		return ie::FullColor{
			node.at("color").except().as<sf::Color>().except(),
			node.get_as<sf::Vector2f>("normal-size").ok_or({})
		};
	}
}
