#include "interactiveSimple.h"

ui::Interactive_Simple::Interactive_Simple(ui::IInteraction *interaction) : interaction(interaction), interact(false), oldInteract(false) {}

void ui::Interactive_Simple::update() {
	if(interact != oldInteract) {
		oldInteract = interact;
		if(interact) {
			interactionManager->addInteraction(*interaction);
		} else {
			interactionManager->deleteInteraction(*interaction);
		}
	}
	interact = false;
}

bool ui::Interactive_Simple::updateInteractions(sf::Vector2f mousePosition) {
	interact = true;
	return true;
}
