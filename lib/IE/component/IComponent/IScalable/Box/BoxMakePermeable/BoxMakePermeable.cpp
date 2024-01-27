#include "BoxMakePermeable.hpp"

namespace ie {
	BoxMakePermeable* BoxMakePermeable::Make::make(InitInfo init_info) {
		return new BoxMakePermeable{std::move(*this), init_info};
	}
	
	BoxMakePermeable::Make::Make(BoxPtr<IScalable::Make>&& object, sf::Vector2f min_size) :
		object(std::move(object)), min_size(min_size) {
	}
	
	BoxMakePermeable::BoxMakePermeable(Make&& make, InitInfo init_info) :
		Box(make.min_size), object_(make.object->make(init_info)) {
	}
	
	BoxMakePermeable::BoxMakePermeable(BoxPtr<IScalable>&& object, sf::Vector2f min_size) :
		Box(min_size), object_(std::move(object)) {
	}
	
	void BoxMakePermeable::init(InitInfo init_info) {
		object_->init(init_info);
	}
	
	bool BoxMakePermeable::update_interactions(sf::Vector2f mouse_position) {
		object_->update_interactions(mouse_position);
		return false;
	}
	
	IScalable& BoxMakePermeable::get_object() {
		return *object_;
	}
	
	const IScalable& BoxMakePermeable::get_object() const {
		return *object_;
	}
	
	BoxMakePermeable* BoxMakePermeable::copy() {
		return new BoxMakePermeable{*this};
	}
}

orl::Option<ie::BoxMakePermeable::Make> ieml::Decode<char, ie::BoxMakePermeable::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxMakePermeable::Make{
		map.at("object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({})
	};
}
