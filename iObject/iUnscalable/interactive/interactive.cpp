#include "interactive.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	Interactive::Interactive() : interactionStack(nullptr) {}
	
	void Interactive::init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) {
		this->interactionStack = &interactionStack;
		this->interactionManager = &interactionManager;
		init(renderTarget, panelManager);
	}
	
	void Interactive::copy(Interactive *interactive) {
		interactive->interactionStack = this->interactionStack;
		interactive->interactionManager = this->interactionManager;
	}
}
