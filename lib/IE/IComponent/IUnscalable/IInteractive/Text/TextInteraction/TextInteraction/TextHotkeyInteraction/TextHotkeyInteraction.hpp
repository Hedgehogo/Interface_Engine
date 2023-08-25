#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicHotkeyInteraction/BasicHotkeyInteraction.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextKeysInteraction/TextKeysInteraction.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	using TextHotkeyInteraction = BasicHotkeyInteraction<Text&>;
	
	template<>
	struct DecodePointer<TextHotkeyInteraction> {
		static bool decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction);
	};
}