#include "pressedInteraction.h"

ui::PressedInteraction::PressedInteraction(ui::ButtonEvent *event, sf::Mouse::Button button) : OneButtonInteraction(event, button), interactionManager(nullptr) {}

void ui::PressedInteraction::init(InteractionManager &interactionManager) {
	this->interactionManager = &interactionManager;
}

bool ui::PressedInteraction::update(sf::Vector2i mousePosition) {
	if(sf::Mouse::isButtonPressed(button)) {
		event->update(mousePosition, true);
	} else {
		event->update(mousePosition, false);
		interactionManager->deleteInteraction(*this);
	}
	return true;
}
