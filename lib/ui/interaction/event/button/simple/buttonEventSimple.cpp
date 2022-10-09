#include "buttonEventSimple.hpp"

namespace ui {
	ButtonEvent_Simple::ButtonEvent_Simple() : ButtonEvent(), mousePosition({0, 0}) {}
	
	void ButtonEvent_Simple::setPressed(bool pressed) {
		if(this->pressed != pressed) {
			this->pressed = pressed;
			if(this->pressed) {
				startPressed();
			} else {
				stopPressed();
			}
		}
		ButtonEvent::setPressed(pressed);
	}
	
	void ButtonEvent_Simple::update(sf::Vector2i mousePosition, bool press) {
		this->mousePosition = mousePosition;
		setPressed(press);
		if(this->pressed) {
			whilePressed();
		} else {
			whileNotPressed();
		}
	}
}
