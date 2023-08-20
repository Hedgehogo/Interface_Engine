#pragma once

#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/textInteraction.hpp"
#include "IE/Interaction/IInteraction/HotkeyInteraction/HotkeyInteraction.hpp"
#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/keys/textKeysInteraction.hpp"
#include "modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
	class TextHotkeyInteraction : public TextInteraction, public HotkeyInteraction {
	public:
		TextHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey>>> && hotkeys, uint startState = 0);
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
		TextHotkeyInteraction* copy() override;
		
		~TextHotkeyInteraction() = default;
	};
	
	template<>
	struct DecodePointer<TextHotkeyInteraction> {
		static bool decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction);
	};
}