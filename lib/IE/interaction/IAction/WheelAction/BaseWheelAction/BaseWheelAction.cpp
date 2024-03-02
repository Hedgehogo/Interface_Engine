#include "BaseWheelAction.hpp"

namespace ie {
	BaseWheelAction::BaseWheelAction() {
	}
	
	auto BaseWheelAction::update(sf::Vector2i mouse_position, int value) -> void {
		if(this->active_ != (value != 0)) {
			this->active_ = (value != 0);
			if(this->active_) {
				start_pressed(mouse_position, value);
			} else {
				stop_pressed(mouse_position, value);
			}
		}
		if(this->active_) {
			while_pressed(mouse_position, value);
		} else {
			while_not_pressed(mouse_position, value);
		}
	}
}
