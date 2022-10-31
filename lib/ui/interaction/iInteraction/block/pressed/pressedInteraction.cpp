
#include "pressedInteraction.hpp"

namespace ui {
	PressedInteraction::PressedInteraction(KeyEvent *event, Key key) : OneKeyInteraction(event, key), interactionManager(nullptr) {}
	
	void PressedInteraction::init(InteractionManager &interactionManager) {
		this->interactionManager = &interactionManager;
	}
	
	void PressedInteraction::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(key)) {
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
		PressedInteraction *pressedInteraction{new PressedInteraction{event->copy(), key}};
		PressedInteraction::copy(pressedInteraction);
		return pressedInteraction;
	}
}
