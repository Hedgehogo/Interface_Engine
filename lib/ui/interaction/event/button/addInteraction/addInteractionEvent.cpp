#include "addInteractionEvent.hpp"

void ui::AddInteractionEvent::startPressed() {
	interactionManager->addInteraction(*interaction);
}

void ui::AddInteractionEvent::stopPressed() {
	interactionManager->deleteInteraction(*interaction);
}

void ui::AddInteractionEvent::whilePressed() {}

void ui::AddInteractionEvent::whileNotPressed() {}

ui::AddInteractionEvent::AddInteractionEvent(ui::IInteraction &interaction) : ButtonEvent_Simple(), interactionManager(nullptr), interaction(&interaction) {}

void ui::AddInteractionEvent::init(InteractionManager &interactionManager) {
	this->interactionManager = &interactionManager;
}

void ui::AddInteractionEvent::setInteraction(ui::IInteraction &interaction) {
	this->interaction = &interaction;
}

void ui::AddInteractionEvent::copy(ui::AddInteractionEvent *addInteractionEvent) {
	addInteractionEvent->interactionManager = this->interactionManager;
}

ui::AddInteractionEvent *ui::AddInteractionEvent::copy() {
	AddInteractionEvent* addInteractionEvent{new AddInteractionEvent{*interaction}};
	addInteractionEvent->init(*this->interactionManager);
	return addInteractionEvent;
}
