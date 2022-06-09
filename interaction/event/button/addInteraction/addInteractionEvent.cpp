#include "addInteractionEvent.h"

void ui::AddInteractionEvent::startPressed(sf::Vector2i	) {
	interactionManager->addInteraction(interaction);
}

void ui::AddInteractionEvent::stopPressed(sf::Vector2i windowPosition) {
	interactionManager->deleteInteraction(interaction);
}

void ui::AddInteractionEvent::whilePressed(sf::Vector2i windowPosition) {}

void ui::AddInteractionEvent::notPressed(sf::Vector2i windowPosition) {}

ui::AddInteractionEvent::AddInteractionEvent(ui::IInteraction &interaction) : ButtonEvent_Simple(), interaction(interaction) {}

void ui::AddInteractionEvent::init(InteractionManager &interactionManager) {
	this->interactionManager = &interactionManager;
}
