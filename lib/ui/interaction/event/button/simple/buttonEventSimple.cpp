#include "buttonEventSimple.hpp"

ui::ButtonEvent_Simple::ButtonEvent_Simple() : ButtonEvent() {}

void ui::ButtonEvent_Simple::update(sf::Vector2i mousePosition, bool press) {
	if(this->pressed != press) {
		this->pressed = press;
		if(this->pressed) {
			startPressed(mousePosition);
		} else {
			stopPressed(mousePosition);
		}
	}
	if(this->pressed) {
		whilePressed(mousePosition);
	} else {
		whileNotPressed(mousePosition);
	}
}
