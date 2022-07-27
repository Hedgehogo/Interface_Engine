#include "interactive.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	Interactive::Interactive() : interactionStack(nullptr) {}
	
	void Interactive::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		this->interactionStack = &interactionStack;
		this->interactionManager = &interactionManager;
		init(renderTarget, drawManager, panelManager);
	}
	
	void Interactive::copy(Interactive *interactive) {
		interactive->interactionStack = this->interactionStack;
		interactive->interactionManager = this->interactionManager;
	}
}
