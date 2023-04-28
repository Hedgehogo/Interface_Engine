#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/hotkey/hotkeyInteraction.hpp"
#include "../keys/textKeysInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {
    class TextHotkeyInteraction : public TextInteraction, public HotkeyInteraction{
    public:
        TextHotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint startState = 0);
		
        void init(Text *text, InteractionManager &interactionManager) override;
		
        TextHotkeyInteraction * copy() override;

        ~TextHotkeyInteraction() = default;
    };
	
	bool convertPointer(const YAML::Node &node, TextHotkeyInteraction *&textHotkeyInteraction);
	
	template<>
	struct DecodePointer<TextHotkeyInteraction> {
		static bool decodePointer(const YAML::Node &node, TextHotkeyInteraction *&textHotkeyInteraction);
	};
}