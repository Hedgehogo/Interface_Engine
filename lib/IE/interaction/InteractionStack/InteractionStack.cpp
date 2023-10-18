#include "InteractionStack.hpp"

namespace ie {
	InteractionStack::InteractionStack(std::vector<BoxPtr<IInteraction> >&& interaction_stack) : interaction_stack(std::move(interaction_stack)) {
	}
	
	IInteraction& InteractionStack::at(std::size_t index) {
		return *interaction_stack.at(index);
	}
	
	void InteractionStack::add(BoxPtr<IInteraction>&& element) {
		interaction_stack.push_back(std::move(element));
	}
	
	bool DecodePointer<InteractionStack>::decode_pointer(const YAML::Node& node, InteractionStack*& interaction_stack) {
		interaction_stack = new InteractionStack{
			conv_def(node["interaction"], std::vector<BoxPtr<IInteraction> >{})
		};
		return true;
	}
}

