#include "BaseInteractive.hpp"

namespace ui {
	BaseInteractiveData::BaseInteractiveData(BoxPtr<IInteraction>&& interaction, InitInfo initInfo) :
		interactionStack(&initInfo.interactionStack),
		interactionManager(&initInfo.interactionManager),
		interaction(std::move(interaction)),
		interact(false),
		oldInteract(false) {
		this->interaction->init({initInfo});
	}
	
	BaseInteractiveData::BaseInteractiveData(BoxPtr<IInteraction>&& interaction) :
		interactionStack(nullptr), interactionManager(nullptr), interaction(std::move(interaction)), interact(false), oldInteract(false) {
	}
	
	void BaseInteractiveData::init(InitInfo initInfo) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
		interaction->init({initInfo});
	}
	
	void BaseInteractiveData::update() {
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
	
	void BaseInteractiveData::updateInteractions() {
		interact = true;
	}
	
	BaseInteractive::BaseInteractive(BoxPtr<IInteraction>&& interaction, InitInfo initInfo) :
		interactive(std::move(interaction), initInfo) {
		initInfo.updateManager.add(*this);
	}
	
	BaseInteractive::BaseInteractive(BoxPtr<IInteraction>&& interaction) :
		interactive(std::move(interaction)) {
	}
	
	void BaseInteractive::init(InitInfo initInfo) {
		interactive.init(initInfo);
		initInfo.updateManager.add(*this);
	}
	
	void BaseInteractive::update() {
		interactive.update();
	}
	
	bool BaseInteractive::updateInteractions(sf::Vector2f) {
		interactive.updateInteractions();
		return true;
	}
}
