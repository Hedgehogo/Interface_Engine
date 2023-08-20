#include "textHotkeyInteraction.hpp"

namespace ui {
	TextHotkeyInteraction::TextHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey>>> && hotkeys, uint startState) : HotkeyInteraction(std::move(hotkeys), startState) {
	}
	
	void TextHotkeyInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextInteraction::init(textInteractionInitInfo);
		for(auto& hotkeys: hotkeyStates) {
			for(auto& hotkey: hotkeys) {
				dynamic_cast<TextKeysInteraction*>(hotkey->interaction.get())->init(textInteractionInitInfo);
			}
		}
	}
	
	TextHotkeyInteraction* TextHotkeyInteraction::copy() {
		auto hotkeyInteraction = new TextHotkeyInteraction{*this};
		TextInteraction::copy(hotkeyInteraction);
		return hotkeyInteraction;
	}
	
	bool DecodePointer<TextHotkeyInteraction>::decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction) {
		textHotkeyInteraction = new TextHotkeyInteraction{
			convDef<std::vector<std::vector<BoxPtr<HotkeyInteraction::Hotkey>>>>(node["hotkeys"], {}),
			convDef(node["start-state"], 0u)
		};
		return true;
	}
}