#include "oneButtonInteraction.hpp"

ui::OneButtonInteraction::OneButtonInteraction(ButtonEvent *event, Key button) : event(event), button(button) {}

ui::OneButtonInteraction::~OneButtonInteraction() {
	delete event;
}

ui::Key ui::OneButtonInteraction::getButton() {
	return button;
}

ui::ButtonEvent *ui::OneButtonInteraction::getEvent() {
	return event;
}

void ui::OneButtonInteraction::setEvent(ui::ButtonEvent *event) {
	delete this->event;
	this->event = event;
}

void ui::OneButtonInteraction::start(sf::Vector2i) {}

bool ui::OneButtonInteraction::update(sf::Vector2i mousePosition) {
	event->update(mousePosition, isKeyPressed(button));
	return false;
}

void ui::OneButtonInteraction::finish(sf::Vector2i mousePosition) {
    event->setPressed(false);
}

ui::OneButtonInteraction *ui::OneButtonInteraction::copy() {
	return new OneButtonInteraction{event->copy(), button};
}
