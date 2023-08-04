#include "interactive.hpp"
#include "../../../interaction/interactionStack/interactionStack.hpp"

namespace ui {
	Interactive::Interactive() : interactionStack(nullptr), interactionManager(nullptr) {
	}
	
	void Interactive::init(InitInfo initInfo) {
		this->interactionStack = &initInfo.interactionStack;
		this->interactionManager = &initInfo.interactionManager;
	}
}
