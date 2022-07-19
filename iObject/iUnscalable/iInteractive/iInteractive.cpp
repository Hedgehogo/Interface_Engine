#include "iInteractive.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	void IInteractive::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->interactionStack = &interactionStack;
		this->interactionManager = &interactionManager;
		init(renderTarget, panelManager);
	}
	
	IInteractive::IInteractive() : interactionStack(nullptr) {}
	
	void IInteractive::copy(IInteractive *iInteractive) {
		iInteractive->interactionStack = this->interactionStack;
		iInteractive->interactionManager = this->interactionManager;
	}
}
