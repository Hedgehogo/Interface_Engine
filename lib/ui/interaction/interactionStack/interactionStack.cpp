#include "interactionStack.hpp"

namespace ui {
	InteractionStack::InteractionStack(std::vector<IInteraction *> &&interactionStack) : interactionStack(std::move(interactionStack)) {}
	
	InteractionStack::~InteractionStack() {
		for(const auto &interaction: interactionStack) {
			delete interaction;
		}
	}
	
	IInteraction *InteractionStack::at(unsigned index) {
		return interactionStack[index];
	}
	
	void InteractionStack::add(IInteraction *element) {
		interactionStack.push_back(element);
	}
}

