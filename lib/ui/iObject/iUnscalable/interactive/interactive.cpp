#include "interactive.hpp"
#include "../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	Interactive::Interactive() : interactionStack(nullptr) {
	}
	
	void Interactive::init(InitInfo initInfo) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
		
		InteractiveInitInfo interactiveInitInfo{initInfo.window, initInfo.renderTarget, initInfo.drawManager, initInfo.updateManager, initInfo.panelManager};
		init(interactiveInitInfo);
	}
	
	void Interactive::copy(Interactive* interactive) {
		interactive->interactionStack = this->interactionStack;
		interactive->interactionManager = this->interactionManager;
	}
}
