#include "BoxSwitch.hpp"

namespace ie {
	BoxSwitch::Make::Make(
		BoxPtr<IScalable::Make>&& inactive_object,
		BoxPtr<IScalable::Make>&& active_object,
		MakeDyn<ISBool> value,
		const sf::Vector2f& min_size
	) :
		inactive_object(std::move(inactive_object)), active_object(std::move(active_object)), value(std::move(value)), min_size(min_size) {
	}
	
	BoxSwitch* BoxSwitch::Make::make(InitInfo init_info) {
		return new BoxSwitch{std::move(*this), init_info};
	}
	
	BoxSwitch::BoxSwitch(Make&& make, InitInfo init_info) :
		Box(make.min_size),
		inactive_object_(make.inactive_object->make(init_info.copy(inactive_draw_manager_))),
		active_object_(make.active_object->make(init_info.copy(active_draw_manager_))),
		value_(make.value.make(init_info.dyn_buffer)) {
		init_info.draw_manager.add(*this);
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
		if(value_.get()) {
			active_draw_manager_.draw();
		} else {
			inactive_draw_manager_.draw();
		}
	}
	
	bool BoxSwitch::update_interactions(sf::Vector2f mouse_position) {
		return value_.get() ? active_object_->update_interactions(mouse_position) : inactive_object_->update_interactions(mouse_position);
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
		return nullptr;
	}
}

orl::Option<ie::BoxSwitch::Make> ieml::Decode<char, ie::BoxSwitch::Make>::decode(ieml::Node const& node) {
	auto map{node.get_map_view().except()};
	return ie::BoxSwitch::Make{
		map.at("inactive-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("active-object").except().as<ie::BoxPtr<ie::IScalable::Make> >().move_except(),
		map.at("value").except().as<ie::MakeDyn<ie::ISBool> >().move_except(),
		map.get_as<sf::Vector2f>("min-size").ok_or({}),
	};
}
