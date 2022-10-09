#include "buttonEvent.hpp"

namespace ui {
	ButtonEvent::ButtonEvent() : pressed(false) {}
	
	void ButtonEvent::setPressed(bool pressed) {
		this->pressed = pressed;
	}
	
	void ButtonEvent::copy(ButtonEvent *buttonEvent) {
		buttonEvent->pressed = this->pressed;
	}
}
