#include "keyEvent.hpp"

namespace ui {
	KeyEvent::KeyEvent() : pressed(false) {
	}
	
	void KeyEvent::init(InteractionInitInfo) {
	}
	
	void KeyEvent::setPressed(bool pressed) {
		this->pressed = pressed;
	}
	
	void KeyEvent::copy(KeyEvent* keyEvent) {
		keyEvent->pressed = this->pressed;
	}
}
