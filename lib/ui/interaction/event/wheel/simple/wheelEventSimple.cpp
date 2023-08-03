#include "wheelEventSimple.hpp"

namespace ui {
	WheelEvent_Simple::WheelEvent_Simple() {
	}
	
	void WheelEvent_Simple::update(sf::Vector2i mousePosition, int value) {
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
