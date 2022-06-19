#include "addInteractionEvent.h"

void ui::AddInteractionEvent::startPressed(sf::Vector2i	) {
	interactionManager->addInteraction(*interaction);
}

void ui::AddInteractionEvent::stopPressed(sf::Vector2i windowPosition) {
	interactionManager->deleteInteraction(*interaction);
}

void ui::AddInteractionEvent::whilePressed(sf::Vector2i windowPosition) {}

void ui::AddInteractionEvent::whileNotPressed(sf::Vector2i) {}

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
