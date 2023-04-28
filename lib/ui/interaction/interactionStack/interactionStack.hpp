#pragma once

#include "../iInteraction/iInteraction.hpp"
#include "../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"
#include <vector>

namespace ui {
	class InteractionStack {
	protected:
		std::vector<IInteraction *> interactionStack;
		
	public:
		explicit InteractionStack(std::vector<IInteraction *> &&interactionStack = {});
		
		virtual ~InteractionStack();
		
		IInteraction *at(unsigned index);
		
		void add(IInteraction *element);
	};

	bool convertPointer(const YAML::Node &node, InteractionStack *&interactionStack);
	
	template<>
	struct DecodePointer<InteractionStack> {
		static bool decodePointer(const YAML::Node &node, InteractionStack *&interactionStack);
	};
}
