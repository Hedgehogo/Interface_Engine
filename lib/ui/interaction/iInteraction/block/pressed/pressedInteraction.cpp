#include <iostream>
#include "pressedInteraction.hpp"

ui::PressedInteraction::PressedInteraction(ui::ButtonEvent *event, Key button) : IInteraction(true), OneButtonInteraction(event, button), interactionManager(nullptr) {
	//std::cout << isBlocked();
}

void ui::PressedInteraction::init(InteractionManager &interactionManager) {
	this->interactionManager = &interactionManager;
}

bool ui::PressedInteraction::update(sf::Vector2i mousePosition) {
	if(isKeyPressed(button)) {
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
