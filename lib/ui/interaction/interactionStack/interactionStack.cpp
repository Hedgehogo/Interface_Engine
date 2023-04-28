#include "interactionStack.hpp"

namespace ui {
	InteractionStack::InteractionStack(std::vector<IInteraction*>&& interactionStack) : interactionStack(std::move(interactionStack)) {
	}
	
	InteractionStack::~InteractionStack() {
		for(const auto& interaction: interactionStack) {
			delete interaction;
		}
	}
	
	IInteraction* InteractionStack::at(unsigned index) {
		return interactionStack[index];
	}
	
	void InteractionStack::add(IInteraction* element) {
		interactionStack.push_back(element);
	}
	
	
	bool DecodePointer<InteractionStack>::decodePointer(const YAML::Node& node, InteractionStack*& interactionStack) {
		interactionStack = new InteractionStack{
			node["interaction"] ? std::vector<IInteraction*>{node["interaction"].as<IInteraction*>()} : node["interaction"].as<std::vector<IInteraction*>>()
		};
		return true;
	}
}

