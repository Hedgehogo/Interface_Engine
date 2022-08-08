#include "interactive.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	Interactive::Interactive() : interactionStack(nullptr) {}
	
	void Interactive::init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) {
		this->interactionStack = &interactionStack;
		this->interactionManager = &interactionManager;
		
		init(renderTarget, drawManager, updateManager, panelManager);
	}
	
	void Interactive::copy(Interactive *interactive) {
		interactive->interactionStack = this->interactionStack;
		interactive->interactionManager = this->interactionManager;
	}
}
