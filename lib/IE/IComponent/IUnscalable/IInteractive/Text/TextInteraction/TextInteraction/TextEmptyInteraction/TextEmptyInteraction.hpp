#pragma once

#include "IE/Interaction/IInteraction/BasicEmptyInteraction/BasicEmptyInteraction.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
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