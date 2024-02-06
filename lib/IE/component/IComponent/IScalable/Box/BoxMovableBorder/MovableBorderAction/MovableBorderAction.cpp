
#include "MovableBorderAction.hpp"
#include "../BoxMovableBorder.hpp"

namespace ie {
	MovableBorderAction* MovableBorderAction::Make::make(BasicActionInitInfo<BoxMovableBorder&> init_info) {
		return new MovableBorderAction{std::move(*this), init_info};
	}
	
	MovableBorderAction::MovableBorderAction(Make&&, BasicActionInitInfo<BoxMovableBorder&> init_info) :
		box_(&init_info.additional) {
	}
	
	void MovableBorderAction::set_box(BoxMovableBorder& box) {
		this->box_ = &box;
	}
	
	void MovableBorderAction::start_pressed() {
		this->active_ = box_->is_in_border(static_cast<sf::Vector2f>(mouse_position_));
		if(this->active_) {
			start_mouse_position_ = mouse_position_;
			start_border_value_ = box_->get_border_value_now();
		}
	}
	
	void MovableBorderAction::stop_pressed() {
		this->active_ = false;
	}
	
	void MovableBorderAction::while_pressed() {
		if(this->active_) {
			sf::Vector2f mouse_offset = static_cast<sf::Vector2f>(mouse_position_ - this->start_mouse_position_);
			float value_offset = 0;
			if(box_->get_is_horizontal_border()) {
				value_offset = mouse_offset.x / box_->get_area_size().x;
			} else {
				value_offset = mouse_offset.y / box_->get_area_size().y;
			}
			box_->set_border_value(this->start_border_value_ + value_offset);
			box_->resize(box_->get_area_size(), box_->get_area_position());
			box_->set_border_value(box_->get_border_value_now());
		}
	}
	
	void MovableBorderAction::while_not_pressed() {
	}
}
