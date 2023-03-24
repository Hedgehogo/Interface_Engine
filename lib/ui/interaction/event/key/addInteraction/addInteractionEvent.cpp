#include "addInteractionEvent.hpp"

namespace ui {
	void AddInteractionEvent::startPressed() {
		interactionManager->addInteraction(*interaction);
	}
	
	void AddInteractionEvent::stopPressed() {
		interactionManager->deleteInteraction(*interaction);
	}
	
	void AddInteractionEvent::whilePressed() {}
	
	void AddInteractionEvent::whileNotPressed() {}
	
	AddInteractionEvent::AddInteractionEvent(IInteraction &interaction) : KeyEvent_Simple(), interactionManager(nullptr), interaction(&interaction) {}
	
	void AddInteractionEvent::init(InteractionManager &interactionManager) {
		this->interactionManager = &interactionManager;
	}
	
	void AddInteractionEvent::setInteraction(IInteraction &interaction) {
		this->interaction = &interaction;
	}
	
	void AddInteractionEvent::copy(AddInteractionEvent *addInteractionEvent) {
		addInteractionEvent->interactionManager = this->interactionManager;
	}
	
	AddInteractionEvent *AddInteractionEvent::copy() {
		AddInteractionEvent *addInteractionEvent{new AddInteractionEvent{*interaction}};
		addInteractionEvent->init(*this->interactionManager);
		return addInteractionEvent;
	}
}
