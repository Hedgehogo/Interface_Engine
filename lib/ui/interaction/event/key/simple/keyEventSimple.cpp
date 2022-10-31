#include "keyEventSimple.hpp"

namespace ui {
	KeyEvent_Simple::KeyEvent_Simple() : KeyEvent(), mousePosition({0, 0}) {}
	
	void KeyEvent_Simple::setPressed(bool pressed) {
		if(this->pressed != pressed) {
			this->pressed = pressed;
			if(this->pressed) {
				startPressed();
			} else {
				stopPressed();
			}
		}
		KeyEvent::setPressed(pressed);
	}
	
	void KeyEvent_Simple::update(sf::Vector2i mousePosition, bool press) {
		this->mousePosition = mousePosition;
		setPressed(press);
		if(this->pressed) {
			whilePressed();
		} else {
			whileNotPressed();
		}
	}
}
