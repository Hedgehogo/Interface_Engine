#include "BoxUninteractive.hpp"

namespace ie {
	BoxUninteractive* BoxUninteractive::Make::make(InitInfo init_info) {
		return new BoxUninteractive{std::move(*this), init_info};
	}
	
	BoxUninteractive::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	BoxUninteractive::BoxUninteractive(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)) {
	}
	
	BoxUninteractive::BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f min_size) : Box(min_size), object_(std::move(object)) {
	}
	
	void BoxUninteractive::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
	}
	
	bool BoxUninteractive::update_interactions(sf::Vector2f mouse_position) {
		return INonInteractive::update_interactions(mouse_position);
	}
	
	IScalable& BoxUninteractive::get_object() {
		return *object_;
	}
	
	const IScalable& BoxUninteractive::get_object() const {
		return *object_;
	}
}

orl::Option<ie::BoxUninteractive::Make> ieml::Decode<char, ie::BoxUninteractive::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxUninteractive::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
