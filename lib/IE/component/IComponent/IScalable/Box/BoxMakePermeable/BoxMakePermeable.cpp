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
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxMakePermeable>::decode_pointer(const YAML::Node& node, BoxMakePermeable*& box_make_permeable) {
		box_make_permeable = new BoxMakePermeable{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;

	}
	*/
}