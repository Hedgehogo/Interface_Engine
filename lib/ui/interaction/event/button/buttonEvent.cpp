#include "buttonEvent.hpp"

ui::ButtonEvent::ButtonEvent() : pressed(false) {}

void ui::ButtonEvent::setPressed(bool pressed) {
	this->pressed = pressed;
}

void ui::ButtonEvent::copy(ui::ButtonEvent *buttonEvent) {
	buttonEvent->pressed = this->pressed;
}

ui::ButtonEvent *ui::ButtonEvent::createFromYaml(const YAML::Node &node) {
    return nullptr;
}
