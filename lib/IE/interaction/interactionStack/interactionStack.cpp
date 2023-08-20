#include "interactionStack.hpp"

namespace ui {
	InteractionStack::InteractionStack(std::vector<BoxPtr<IInteraction> >&& interactionStack) : interactionStack(std::move(interactionStack)) {
	}
	
	IInteraction& InteractionStack::at(std::size_t index) {
		return *interactionStack.at(index);
	}
	
	void InteractionStack::add(BoxPtr<IInteraction>&& element) {
		interactionStack.push_back(std::move(element));
	}
	
	bool DecodePointer<InteractionStack>::decodePointer(const YAML::Node& node, InteractionStack*& interactionStack) {
		interactionStack = new InteractionStack{
			convDef(node["interaction"], std::vector<BoxPtr<IInteraction> >{})
		};
		return true;
	}
}

