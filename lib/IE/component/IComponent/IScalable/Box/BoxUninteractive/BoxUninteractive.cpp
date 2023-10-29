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
	
	void BoxUninteractive::init(InitInfo init_info) {
		object_->init(init_info);
	}
	
	void BoxUninteractive::resize(sf::Vector2f size, sf::Vector2f position) {
		IComponentObject::resize(size, position);
	}
	
	bool BoxUninteractive::update_interactions(sf::Vector2f mouse_position) {
		return IUninteractive::update_interactions(mouse_position);
	}
	
	IScalable& BoxUninteractive::get_object() {
		return *object_;
	}
	
	const IScalable& BoxUninteractive::get_object() const {
		return *object_;
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxUninteractive>::decode_pointer(const YAML::Node& node, BoxUninteractive*& box_uninteractive) {
		box_uninteractive = new BoxUninteractive{
			node["object"].as<BoxPtr<IScalable> >(),
			conv_def(node["min-size"], sf::Vector2f{})
		};
		return true;

	}
	*/
	
	BoxUninteractive* BoxUninteractive::copy() {
		return new BoxUninteractive{*this};
	}
}