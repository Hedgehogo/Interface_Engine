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
	return IBlockInteraction::update(mousePosition);
}

void ui::PressedInteraction::copy(ui::PressedInteraction *pressedInteraction) {
	pressedInteraction->interactionManager = this->interactionManager;
}

ui::PressedInteraction *ui::PressedInteraction::copy() {
	PressedInteraction* pressedInteraction{new PressedInteraction{event->copy(), button}};
	PressedInteraction::copy(pressedInteraction);
	return pressedInteraction;
}
