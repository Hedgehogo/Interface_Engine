#include "buttonEventSimple.hpp"

ui::ButtonEvent_Simple::ButtonEvent_Simple() : ButtonEvent(), mousePosition({0, 0}) {}

void ui::ButtonEvent_Simple::setPressed(bool pressed) {
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

void ui::ButtonEvent_Simple::update(sf::Vector2i mousePosition, bool press) {
    this->mousePosition = mousePosition;
    setPressed(press);
	if(this->pressed) {
        whilePressed();
	} else {
        whileNotPressed();
	}
}
