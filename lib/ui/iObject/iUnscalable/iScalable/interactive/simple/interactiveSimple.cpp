#include "interactiveSimple.hpp"

namespace ui {
	Interactive_Simple::Interactive_Simple(IInteraction *interaction) : interaction(interaction), interact(false), oldInteract(false) {
	}
	
	void Interactive_Simple::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, IPanelManager &panelManager) {
		updateManager.add(*this);
	}
	
	void Interactive_Simple::update() {
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
	
	bool Interactive_Simple::updateInteractions(sf::Vector2f) {
		interact = true;
		return true;
	}
	
	void Interactive_Simple::copy(Interactive_Simple *interactive_Simple) {
		Interactive::copy(interactive_Simple);
		interactive_Simple->interact = this->interact;
		interactive_Simple->oldInteract = this->oldInteract;
	}
}
