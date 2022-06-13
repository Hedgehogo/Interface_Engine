#include "iInteractive.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	void IInteractive::init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) {
		this->interactionStack = &interactionStack;
		this->interactionManager = &interactionManager;
		init(window, parent, overlayStack);
	}
	
	IInteractive::IInteractive() : interactionStack(nullptr) {}
	
	void IInteractive::copy(IInteractive *iInteractive) {
		iInteractive->interactionStack = this->interactionStack;
		iInteractive->interactionManager = this->interactionManager;
	}
}
