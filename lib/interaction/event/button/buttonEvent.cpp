#include "buttonEvent.h"

ui::ButtonEvent::ButtonEvent() : pressed(false) {}

void ui::ButtonEvent::setPressed(bool pressed) {
	this->pressed = pressed;
}

void ui::ButtonEvent::copy(ui::ButtonEvent *buttonEvent) {
	buttonEvent->pressed = this->pressed;
}
