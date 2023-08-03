#pragma once

#include "ui/iObject/iUnscalable/interactive/text/interaction/interaction/textInteraction.hpp"
#include "ui/interaction/iInteraction/hotkey/hotkeyInteraction.hpp"
#include "ui/iObject/iUnscalable/interactive/text/interaction/interaction/keys/textKeysInteraction.hpp"
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