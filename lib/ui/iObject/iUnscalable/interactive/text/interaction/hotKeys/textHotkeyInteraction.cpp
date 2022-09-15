#include "textHotkeyInteraction.hpp"

void operator >> (const YAML::Node& node, ui::HotkeyInteraction::Hotkey& hotkey){
    uint state = UINT32_MAX;
    ui::ButtonsInteraction *interaction{nullptr};
    
}

namespace ui {
    TextHotkeyInteraction::TextHotkeyInteraction(std::vector<std::vector<Hotkey *>> hotkeys, uint startState) : HotkeyInteraction(hotkeys, startState) {}

    void TextHotkeyInteraction::init(ui::Text *text) {
        TextInteraction::init(text);
        for (auto hotkeys : hotkeyStates) {
            for (auto hotkey : hotkeys) {
                dynamic_cast<TextButtonsInteraction *>(hotkey->interaction)->init(text);
            }
        }
    }

    TextHotkeyInteraction *TextHotkeyInteraction::copy() {
        return new TextHotkeyInteraction{hotkeyStates, static_cast<uint>(std::distance(hotkeyStates.begin(), std::vector<std::vector<Hotkey*>>::iterator(nowHotkeys)))};
    }

    TextHotkeyInteraction *TextHotkeyInteraction::createFromYaml(const YAML::Node &node) {
        std::vector<std::vector<Hotkey *>> hotkeys;
        uint startState{0};

        if (node["start-state"]) node["start-state"] >> startState;

        if (node["hotkeys"]){
            hotkeys.resize(node["hotkeys"].size());
            uint i{0};
            for (auto& state : node["hotkeys"]) {
                hotkeys.resize(state.size());
                uint j{0};
                for (auto& hotkey : state) {
                    hotkeys[i][j] = createHotkeyFromYaml(hotkey);
                    ++j;
                }
                ++i;
            }
        }

        return new TextHotkeyInteraction{hotkeys, startState};
    }
} // ui