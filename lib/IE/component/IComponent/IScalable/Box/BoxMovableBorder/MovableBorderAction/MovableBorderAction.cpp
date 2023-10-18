
#include "MovableBorderAction.hpp"
#include "../BoxMovableBorder.hpp"

namespace ie {
	MovableBorderAction* MovableBorderAction::Make::make(BasicActionInitInfo<BoxMovableBorder&> init_info) {
		return new MovableBorderAction{std::move(*this), init_info};
	}
	
	MovableBorderAction::MovableBorderAction(Make&&, BasicActionInitInfo<BoxMovableBorder&> init_info) :
		box(&init_info.additional) {
	}
	
	MovableBorderAction::MovableBorderAction() : box(nullptr) {
	}
	
	void MovableBorderAction::init(BasicActionInitInfo<BoxMovableBorder&> init_info) {
		box = &init_info.additional;
	}
	
	void MovableBorderAction::set_box(BoxMovableBorder& box) {
		this->box = &box;
	}
	
	void MovableBorderAction::start_pressed() {
		this->active = box->is_in_border(static_cast<sf::Vector2f>(mouse_position));
		if(this->active) {
			start_mouse_position = mouse_position;
			start_border_value = box->get_border_value_now();
		}
	}
	
	void MovableBorderAction::stop_pressed() {
		this->active = false;
	}
	
	void MovableBorderAction::while_pressed() {
		if(this->active) {
			sf::Vector2f mouse_offset = static_cast<sf::Vector2f>(mouse_position - this->start_mouse_position);
			float value_offset = 0;
			if(box->get_is_horizontal_border()) {
				value_offset = mouse_offset.x / box->get_area_size().x;
			} else {
				value_offset = mouse_offset.y / box->get_area_size().y;
			}
			box->set_border_value(this->start_border_value + value_offset);
			box->resize(box->get_area_size(), box->get_area_position());
			box->set_border_value(box->get_border_value_now());
		}
	}
	
	void MovableBorderAction::while_not_pressed() {
	}
	
	MovableBorderAction* MovableBorderAction::copy() {
		return new MovableBorderAction{*this};
	}}
