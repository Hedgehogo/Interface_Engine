#include "textHotkeyInteraction.hpp"

namespace ui {
	TextHotkeyInteraction::TextHotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint startState) : HotkeyInteraction(hotkeys, startState) {
	}
	
	void TextHotkeyInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextInteraction::init(textInteractionInitInfo);
		for(auto hotkeys: hotkeyStates) {
			for(auto hotkey: hotkeys) {
				dynamic_cast<TextKeysInteraction*>(hotkey->interaction)->init(textInteractionInitInfo);
			}
		}
	}
	
	TextHotkeyInteraction* TextHotkeyInteraction::copy() {
		auto hotkeyInteraction = new TextHotkeyInteraction{hotkeyStates, static_cast<uint>(std::distance(hotkeyStates.begin(), std::vector<std::vector<Hotkey*>>::iterator(nowHotkeys)))};
		TextInteraction::copy(hotkeyInteraction);
		return hotkeyInteraction;
	}
	
	bool DecodePointer<TextHotkeyInteraction>::decodePointer(const YAML::Node& node, TextHotkeyInteraction*& textHotkeyInteraction) {
		std::vector<std::vector<HotkeyInteraction::Hotkey*>> hotkeys;
		uint startState{0};
		
		if(node["start-state"])
			node["start-state"] >> startState;
		
		if(node["hotkeys"]) {
			hotkeys.resize(node["hotkeys"].size());
			uint i{0};
			for(auto& state: node["hotkeys"]) {
				hotkeys.resize(state.size());
				uint j{0};
				for(auto& hotkey: state) {
					hotkey >> hotkeys[i][j];
					++j;
				}
				++i;
			}
		}
		
		textHotkeyInteraction = new TextHotkeyInteraction{hotkeys, startState};
		return true;
	}
}