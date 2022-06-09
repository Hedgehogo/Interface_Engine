#include "interactionStack.h"

InteractionStack::InteractionStack(std::vector<ui::IInteraction *> &&interactionStack) : interactionStack(std::move(interactionStack)){}

ui::IInteraction *InteractionStack::at(unsigned index) {
	return interactionStack[index];
}

void InteractionStack::add(ui::IInteraction *element) {
	interactionStack.push_back(element);
}
