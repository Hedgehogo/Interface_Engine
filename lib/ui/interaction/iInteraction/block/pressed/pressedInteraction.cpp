
#include "pressedInteraction.hpp"

namespace ui {
	PressedInteraction::PressedInteraction(ButtonEvent *event, Key button) : OneButtonInteraction(event, button), interactionManager(nullptr) {}
	
	void PressedInteraction::init(InteractionManager &interactionManager) {
		this->interactionManager = &interactionManager;
	}
	
	void PressedInteraction::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(button)) {
			event->update(mousePosition, true);
		} else {
			event->update(mousePosition, false);
			interactionManager->deleteInteraction(*this);
		}
	}
	
	void PressedInteraction::copy(PressedInteraction *pressedInteraction) {
		pressedInteraction->interactionManager = this->interactionManager;
	}
	
	PressedInteraction *PressedInteraction::copy() {
		PressedInteraction *pressedInteraction{new PressedInteraction{event->copy(), button}};
		PressedInteraction::copy(pressedInteraction);
		return pressedInteraction;
	}
}
