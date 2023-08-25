
#include "BasicPressedInteraction.hpp"

namespace ui {
	PressedInteraction::PressedInteraction(BoxPtr<KeyEvent>&& event, Key key) : OneKeyInteraction(std::move(event), key), interactionManager(nullptr) {
	}
	
	void PressedInteraction::init(InteractionInitInfo interactionInitInfo) {
		this->interactionManager = &interactionInitInfo.interactionManager;
	}
	
	void PressedInteraction::update(sf::Vector2i mousePosition) {
		if(KeyHandler::isKeyPressed(key)) {
			event->update(mousePosition, true);
		} else {
			event->update(mousePosition, false);
			interactionManager->deleteInteraction(*this);
		}
	}
	
	PressedInteraction* PressedInteraction::copy() {
		return new PressedInteraction{*this};
	}
}
