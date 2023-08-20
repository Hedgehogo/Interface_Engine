#include "KeyEvent.hpp"

namespace ui {
	KeyEvent::KeyEvent() : pressed(false) {
	}
	
	void KeyEvent::init(InteractionInitInfo) {
	}
	
	void KeyEvent::setPressed(bool pressed) {
		this->pressed = pressed;
	}
}
