#include "BoxSwitch.hpp"

namespace ie {
	BoxSwitch::Make::Make(BoxPtr<IScalable::Make>&& inactive_object, BoxPtr<IScalable::Make>&& active_object, PSbool value, const sf::Vector2f& min_size) :
		inactive_object(std::move(inactive_object)), active_object(std::move(active_object)), value(value), min_size(min_size) {
	}
	
	BoxSwitch* BoxSwitch::Make::make(InitInfo init_info) {
		return new BoxSwitch{std::move(*this), init_info};
	}
	
	BoxSwitch::BoxSwitch(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		inactive_object_(make.inactive_object->make(init_info.copy(inactive_draw_manager_))),
		active_object_(make.active_object->make(init_info.copy(active_draw_manager_))),
		value_(make.value) {
		init_info.draw_manager.add(*this);
	}
	
	BoxSwitch::BoxSwitch(BoxPtr<IScalable>&& inactive_object, BoxPtr<IScalable>&& active_object, PSbool value, const sf::Vector2f& min_size) :
		Box(min_size), inactive_object_(std::move(inactive_object)), active_object_(std::move(active_object)), value_(value) {
	}
	
	BoxSwitch::BoxSwitch(const BoxSwitch& other) :
		Box(other), inactive_object_(other.inactive_object_), active_object_(other.active_object_), value_(other.value_) {
	}
	
	void BoxSwitch::init(InitInfo init_info) {
		inactive_object_->init(init_info.copy(inactive_draw_manager_));
		active_object_->init(init_info.copy(active_draw_manager_));
		init_info.draw_manager.add(*this);
	}
	
	void BoxSwitch::set_position(sf::Vector2f position) {
		layout_.set_position(position);
		inactive_object_->set_position(position);
		active_object_->set_position(position);
	}
	
	void BoxSwitch::move(sf::Vector2f position) {
		layout_.move(position);
		inactive_object_->move(position);
		active_object_->move(position);
	}
	
	void BoxSwitch::set_size(sf::Vector2f size) {
		layout_.set_size(size);
		inactive_object_->set_size(size);
		active_object_->set_size(size);
	}
	
	void BoxSwitch::resize(sf::Vector2f size, sf::Vector2f position) {
		layout_.resize(size, position);
		inactive_object_->resize(size, position);
		active_object_->resize(size, position);
	}
	
	void BoxSwitch::draw() {
		if(value_->get_value()) {
			active_draw_manager_.draw();
		} else {
			inactive_draw_manager_.draw();
		}
	}
	
	bool BoxSwitch::update_interactions(sf::Vector2f mouse_position) {
		return value_->get_value() ? active_object_->update_interactions(mouse_position) : inactive_object_->update_interactions(mouse_position);
	}
	
	IScalable& BoxSwitch::get_first_object() {
		return *inactive_object_;
	}
	
	const IScalable& BoxSwitch::get_first_object() const {
		return *inactive_object_;
	}
	
	IScalable& BoxSwitch::get_second_object() {
		return *active_object_;
	}
	
	const IScalable& BoxSwitch::get_second_object() const {
		return *active_object_;
	}
	
	BoxSwitch* BoxSwitch::copy() {
		return new BoxSwitch{*this};
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<BoxSwitch>::decode_pointer(const YAML::Node& node, BoxSwitch*& box_switcher) {
		box_switcher = new BoxSwitch{
			node["inactive-object"].as<BoxPtr<IScalable>>(),
			node["active-object"].as<BoxPtr<IScalable> >(),
			Buffer::get<Sbool>(node["value"]),
			conv_def(node["min-size"],sf::Vector2f{})
		};
		return true;

	}
	*/
}