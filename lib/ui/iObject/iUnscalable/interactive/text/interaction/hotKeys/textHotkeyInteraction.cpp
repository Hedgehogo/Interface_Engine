#include "textHotkeyInteraction.hpp"

namespace ui {
    TextHotkeyInteraction::TextHotkeyInteraction(std::vector<std::vector<Hotkey *>> hotkeys, uint startState) : HotkeyInteraction(hotkeys, startState) {}

    void TextHotkeyInteraction::init(Text *text) {
        TextInteraction::init(text);
        for (auto hotkeys : hotkeyStates) {
            for (auto hotkey : hotkeys) {
                dynamic_cast<TextKeysInteraction *>(hotkey->interaction)->init(text);
            }
        }
    }

    TextHotkeyInteraction *TextHotkeyInteraction::copy() {
        return new TextHotkeyInteraction{hotkeyStates, static_cast<uint>(std::distance(hotkeyStates.begin(), std::vector<std::vector<Hotkey*>>::iterator(nowHotkeys)))};
    }

    bool convertPointer(const YAML::Node &node, TextHotkeyInteraction *&textHotkeyInteraction) {
        std::vector<std::vector<HotkeyInteraction::Hotkey *>> hotkeys;
        uint startState{0};

        if (node["start-state"]) node["start-state"] >> startState;

        if (node["hotkeys"]){
            hotkeys.resize(node["hotkeys"].size());
            uint i{0};
            for (auto& state : node["hotkeys"]) {
                hotkeys.resize(state.size());
                uint j{0};
                for (auto& hotkey : state) {
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