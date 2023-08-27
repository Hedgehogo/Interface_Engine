#pragma once

#include "IE/IComponent/IUnscalable/Text/TextInteraction/TextInteraction/TextInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicHotkeyInteraction/BasicHotkeyInteraction.hpp"
#include "IE/IComponent/IUnscalable/Text/TextInteraction/TextInteraction/TextKeysInteraction/TextKeysInteraction.hpp"
#include "IE/Modules/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ie {
	using TextHotkeyInteraction = BasicHotkeyInteraction<Text&>;
	
	template<>
	struct DecodePointer<TextHotkeyInteraction> {
		static bool decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction);
	};
}