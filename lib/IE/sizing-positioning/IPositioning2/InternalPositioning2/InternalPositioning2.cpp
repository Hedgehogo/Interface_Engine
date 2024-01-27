#include "InternalPositioning2.hpp"

namespace ie {
	InternalPositioning2::Make::Make(sf::Vector2f coefficient) : coefficient(coefficient) {
	}
	
	InternalPositioning2* InternalPositioning2::Make::make(Positioning2InitInfo init_info) {
		return new InternalPositioning2{std::move(*this), init_info};
	}
	
	InternalPositioning2::InternalPositioning2(Make&& make, Positioning2InitInfo) :
		vertical_(std::max(0.f, std::min(1.f, make.coefficient.y))),
		horizontal_(std::max(0.f, std::min(1.f, make.coefficient.x))) {
	}
	
	InternalPositioning2::InternalPositioning2(sf::Vector2f coefficient) :
		vertical_(std::max(0.f, std::min(1.f, coefficient.y))), horizontal_(std::max(0.f, std::min(1.f, coefficient.x))) {
	}
	
	void InternalPositioning2::init(sf::RenderTarget&) {
	}
	
	sf::Vector2f InternalPositioning2::find_position(sf::Vector2f parent_position, sf::Vector2f parent_size, sf::Vector2f object_size) {
		return {
			horizontal_.find_position(parent_position.x, object_size.x, parent_size.x, 0),
			vertical_.find_position(parent_position.y, object_size.y, parent_size.y, 0)
		};
	}
	
	InternalPositioning2* InternalPositioning2::copy() {
		return new InternalPositioning2{*this};
	}
}

orl::Option<ie::InternalPositioning2::Make> ieml::Decode<char, ie::InternalPositioning2::Make>::decode(ieml::Node const& node) {
	return {{node.at("coefficient").except().as<sf::Vector2f>().except()}};
}
