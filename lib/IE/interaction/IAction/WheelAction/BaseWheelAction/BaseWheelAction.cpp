#include "BaseWheelAction.hpp"

namespace ie {
	BaseWheelAction::BaseWheelAction() {
	}
	
	void BaseWheelAction::update(sf::Vector2i mousePosition, int value) {
		if(this->active != (value != 0)) {
			this->active = (value != 0);
			if(this->active) {
				startPressed(mousePosition, value);
			} else {
				stopPressed(mousePosition, value);
			}
		}
		if(this->active) {
			whilePressed(mousePosition, value);
		} else {
			whileNotPressed(mousePosition, value);
		}
	}
}
