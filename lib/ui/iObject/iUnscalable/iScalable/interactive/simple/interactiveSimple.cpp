#include "interactiveSimple.hpp"

namespace ui {
	Interactive_Simple::Interactive_Simple(BoxPtr<IInteraction>&& interaction) :
		interactionStack(nullptr), interactionManager(nullptr), interaction(std::move(interaction)), interact(false), oldInteract(false) {
	}
	
	void Interactive_Simple::init(InitInfo initInfo) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
		initInfo.updateManager.add(*this);
		interaction->init({initInfo});
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
}
