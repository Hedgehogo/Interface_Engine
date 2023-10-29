#pragma once

#include "../IInteraction/IInteraction.hpp"
#include "IE/modules/yaml-cpp/yaml.hpp"
#include <cstddef>
#include <yaml-cpp/yaml.h>
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
	
	/*old_yaml_decode_pointer
	template<>
	struct DecodePointer<InteractionStack> {
		static bool decode_pointer(const YAML::Node& node, InteractionStack*& interaction_stack);
	};
	*/
}