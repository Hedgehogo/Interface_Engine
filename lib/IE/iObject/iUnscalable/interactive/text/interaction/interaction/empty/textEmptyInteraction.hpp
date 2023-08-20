#pragma once

#include "IE/Interaction/IInteraction/EmptyInteraction/EmptyInteraction.hpp"
#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/textInteraction.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextEmptyInteraction : public EmptyInteraction, public TextInteraction {
	public:
		TextEmptyInteraction* copy() override;
	};
	
	template<>
	struct DecodePointer<TextEmptyInteraction> {
		static bool decodePointer(const YAML::Node&, TextEmptyInteraction*& textEmptyInteraction);
	};
}