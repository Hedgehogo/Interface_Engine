#include "interactiveSimple.hpp"

ui::Interactive_Simple::Interactive_Simple(ui::IInteraction *interaction) : interaction(interaction), interact(false), oldInteract(false) {}

void ui::Interactive_Simple::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) {
	updateManager.add(*this);
}

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

bool ui::Interactive_Simple::updateInteractions(sf::Vector2f) {
	interact = true;
	return true;
}

void ui::Interactive_Simple::copy(ui::Interactive_Simple *interactive_Simple) {
	Interactive::copy(interactive_Simple);
	interactive_Simple->interact = this->interact;
	interactive_Simple->oldInteract = this->oldInteract;
}
