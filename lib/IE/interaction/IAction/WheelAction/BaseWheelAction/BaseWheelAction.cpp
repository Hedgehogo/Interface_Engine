#include "BaseWheelAction.hpp"

namespace ie {
	BaseWheelAction::BaseWheelAction() {
	}
	
	void BaseWheelAction::update(sf::Vector2i mouse_position, int value) {
		if(this->active != (value != 0)) {
			this->active = (value != 0);
			if(this->active) {
				start_pressed(mouse_position, value);
			} else {
				stop_pressed(mouse_position, value);
			}
		}
		if(this->active) {
			while_pressed(mouse_position, value);
		} else {
			while_not_pressed(mouse_position, value);
		}
	}
}
