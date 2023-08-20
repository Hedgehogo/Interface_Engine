#include "BaseKeyEvent.hpp"

namespace ui {
	BaseKeyEvent::BaseKeyEvent() : KeyEvent(), mousePosition({0, 0}) {
	}
	
	void BaseKeyEvent::setPressed(bool pressed) {
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
	
	void BaseKeyEvent::update(sf::Vector2i mousePosition, bool press) {
		this->mousePosition = mousePosition;
		setPressed(press);
		if(this->pressed) {
			whilePressed();
		} else {
			whileNotPressed();
		}
	}
	
	void BaseKeyEvent::init(InteractionInitInfo interactionInitInfo) {
		KeyEvent::init(interactionInitInfo);
	}
}
