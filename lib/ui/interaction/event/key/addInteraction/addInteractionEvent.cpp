#include "addInteractionEvent.hpp"

namespace ui {
	void AddInteractionEvent::startPressed() {
		interactionManager->addInteraction(*interaction);
	}
	
	void AddInteractionEvent::stopPressed() {
		interactionManager->deleteInteraction(*interaction);
	}
	
	void AddInteractionEvent::whilePressed() {
	}
	
	void AddInteractionEvent::whileNotPressed() {
	}
	
	AddInteractionEvent::AddInteractionEvent(IInteraction& interaction) : KeyEvent_Simple(), interactionManager(nullptr), interaction(&interaction) {
	}
	
	void AddInteractionEvent::init(InteractionInitInfo interactionInitInfo) {
		interactionManager = &interactionInitInfo.interactionManager;
	}
	
	void AddInteractionEvent::setInteraction(IInteraction& interaction) {
		this->interaction = &interaction;
	}
	
	AddInteractionEvent* AddInteractionEvent::copy() {
		return new AddInteractionEvent{*this};
	}
}
