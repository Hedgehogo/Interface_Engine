#include "textHotKeyInteraction.hpp"

namespace ui {
    TextHotKeyInteraction::TextHotKeyInteraction(std::vector<std::vector<Hotkey *>> hotkeys, uint state) : HotkeyInteraction(hotkeys, state) {}

    void TextHotKeyInteraction::init(ui::Text *text) {
        TextInteraction::init(text);
        for (auto hotkeys : hotkeyStates) {
            for (auto hotkey : hotkeys) {
                dynamic_cast<TextButtonsInteractions *>(hotkey->interaction)->init(text);
            }
        }
    }

    TextHotKeyInteraction *TextHotKeyInteraction::copy() {
        return new TextHotKeyInteraction{hotkeyStates, static_cast<uint>(std::distance(hotkeyStates.begin(), std::vector<std::vector<Hotkey*>>::iterator(nowHotkeys)))};
    }
} // ui