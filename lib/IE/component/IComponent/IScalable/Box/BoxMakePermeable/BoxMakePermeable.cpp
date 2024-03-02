#include "BoxMakePermeable.hpp"

namespace ie {
	BoxMakePermeable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	auto BoxMakePermeable::Make::make(InitInfo init_info) -> BoxMakePermeable* {
		return new BoxMakePermeable{std::move(*this), init_info};
	}
	
	BoxMakePermeable::BoxMakePermeable(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)) {
	}
	
	auto BoxMakePermeable::update_interactions(sf::Vector2f mouse_position) -> bool {
		object_->update_interactions(mouse_position);
		return false;
	}
	
	auto BoxMakePermeable::get_object() -> IScalable& {
		return *object_;
	}
	
	auto BoxMakePermeable::get_object() const -> const IScalable& {
		return *object_;
	}
}

auto ieml::Decode<char, ie::BoxMakePermeable::Make>::decode(ieml::Node const& node) -> orl::Option<ie::BoxMakePermeable::Make> {
	auto map{node.get_map_view().except()};
	return ie::BoxMakePermeable::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().except(),
		map.get_as<sf::Vector2f>("min-size").except().ok_or({})
	};
}
