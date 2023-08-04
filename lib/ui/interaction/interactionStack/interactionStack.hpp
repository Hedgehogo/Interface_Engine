#pragma once

#include "../iInteraction/iInteraction.hpp"
#include "../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include <vector>

namespace ui {
	class InteractionStack {
	protected:
		std::vector<BoxPtr<IInteraction> > interactionStack;
	
	public:
		explicit InteractionStack(std::vector<BoxPtr<IInteraction> >&& interactionStack = {});
		
		IInteraction& at(std::size_t index);
		
		void add(BoxPtr<IInteraction>&& element);
	};
	
	template<>
	struct DecodePointer<InteractionStack> {
		static bool decodePointer(const YAML::Node& node, InteractionStack*& interactionStack);
	};
}
