#include "BoxAlternative.hpp"
#include <algorithm>

namespace ie {
	BoxAlternative::Make::Make(BoxPtr<IScalable::Make>&& top_object, BoxPtr<IScalable::Make>&& bottom_object, sf::Vector2f min_size) :
		top_object(std::move(top_object)), bottom_object(std::move(bottom_object)), min_size(min_size) {
	}
	
	BoxAlternative* BoxAlternative::Make::make(InitInfo init_info) {
		return new BoxAlternative{std::move(*this), init_info};
	}
	
	BoxAlternative::BoxAlternative(Make&& make, InitInfo init_info) :
		Box(make.min_size), bottom_object_(make.bottom_object->make(init_info)), top_object_(make.top_object->make(init_info)) {
	}
	
	BoxAlternative::BoxAlternative(BoxPtr<IScalable>&& top_object, BoxPtr<IScalable>&& bottom_object, sf::Vector2f min_size) :
		Box(min_size), bottom_object_(std::move(bottom_object)), top_object_(std::move(top_object)) {
	}
	
	void BoxAlternative::init(InitInfo init_info) {
		top_object_->init(init_info);
		bottom_object_->init(init_info);
	}
	
	bool BoxAlternative::update_interactions(sf::Vector2f mouse_position) {
		return top_object_->update_interactions(mouse_position) || bottom_object_->update_interactions(mouse_position);
	}
	
	void BoxAlternative::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		top_object_->resize(size, position);
		bottom_object_->resize(size, position);
	}
	
	IScalable& BoxAlternative::get_first_object() {
		return *top_object_;
	}
	
	const IScalable& BoxAlternative::get_first_object() const {
		return *top_object_;
	}
	
	IScalable& BoxAlternative::get_second_object() {
		return *bottom_object_;
	}
	
	const IScalable& BoxAlternative::get_second_object() const {
		return *bottom_object_;
	}
	
	BoxAlternative* BoxAlternative::copy() {
		return new BoxAlternative{*this};
	}
	
	bool DecodePointer<BoxAlternative>::decode_pointer(const YAML::Node& node, BoxAlternative*& box_with_alternative_object) {
		box_with_alternative_object = new BoxAlternative{
			node["top-object"].as<BoxPtr<IScalable> >(),
			node["bottom-object"].as<BoxPtr<IScalable> >(),
			conv_def(node["min-size"], sf::Vector2f{}),
		};
		return true;
	}
}
