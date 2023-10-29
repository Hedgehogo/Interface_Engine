#include "InteractionStack.hpp"

namespace ie {
	InteractionStack::InteractionStack(std::vector<BoxPtr<IInteraction> >&& interaction_stack) : interaction_stack_(std::move(interaction_stack)) {
	}
	
	IInteraction& InteractionStack::at(size_t index) {
		return *interaction_stack_.at(index);
	}
	
	void InteractionStack::add(BoxPtr<IInteraction>&& element) {
		interaction_stack_.push_back(std::move(element));
	}
	
	/*old_yaml_decode_pointer_impl
	bool DecodePointer<InteractionStack>::decode_pointer(const YAML::Node& node, InteractionStack*& interaction_stack) {
		interaction_stack = new InteractionStack{
			conv_def(node["interaction"], std::vector<BoxPtr<IInteraction> >{})
		};
		return true;

	}
	*/
}

