#pragma once

#include "../IInteraction/IInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml-builder/yaml-builder.hpp"
#include <vector>

namespace ie {
	class InteractionStack {
	public:
		explicit InteractionStack(std::vector<BoxPtr<IInteraction> >&& interaction_stack = {});
		
		IInteraction& at(size_t index);
		
		void add(BoxPtr<IInteraction>&& element);
	
	protected:
		std::vector<BoxPtr<IInteraction> > interaction_stack_;
	};
	
	template<>
	struct DecodePointer<InteractionStack> {
		static bool decode_pointer(const YAML::Node& node, InteractionStack*& interaction_stack);
	};
}