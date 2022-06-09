#include "oneButtonInteraction.h"

ui::OneButtonInteraction::OneButtonInteraction(ButtonEvent *event, sf::Mouse::Button button) : event(event), button(button) {}

ui::OneButtonInteraction::~OneButtonInteraction() {
	delete event;
}

void ui::OneButtonInteraction::start(sf::Vector2i) {}

bool ui::OneButtonInteraction::update(sf::Vector2i mousePosition) {
	event->update(mousePosition, sf::Mouse::isButtonPressed(button));
	return false;
}

void ui::OneButtonInteraction::finish(sf::Vector2i) {}
