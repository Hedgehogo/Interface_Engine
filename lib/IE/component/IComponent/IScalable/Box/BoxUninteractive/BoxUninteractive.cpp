#include "BoxUninteractive.hpp"

namespace ie {
	BoxUninteractive::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	auto BoxUninteractive::Make::make(InitInfo init_info) -> BoxUninteractive* {
		return new BoxUninteractive{std::move(*this), init_info};
	}
	
	BoxUninteractive::BoxUninteractive(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)) {
	}
	
	BoxUninteractive::BoxUninteractive(BoxPtr<IScalable>&& object, sf::Vector2f min_size) : Box(min_size), object_(std::move(object)) {
	}
	
	auto BoxUninteractive::resize(sf::Vector2f size, sf::Vector2f position) -> void {
		IComponentObject::resize(size, position);
	}
	
	auto BoxUninteractive::update_interactions(sf::Vector2f mouse_position) -> bool {
		return INonInteractive::update_interactions(mouse_position);
	}
	
	auto BoxUninteractive::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxUninteractive::get_object() const -> IScalable const& {
		return *object_;
	}
}

auto ieml::Decode<char, ie::BoxUninteractive::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxUninteractive::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxUninteractive::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
