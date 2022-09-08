#include "hotkeyInteraction.hpp"

namespace ui {
    HotkeyInteraction::Hotkey::Hotkey(ButtonsInteraction *interaction, int state)  : interaction(interaction), state(state)  {}

    HotkeyInteraction::Hotkey::Hotkey(uint state) : state(state), interaction(nullptr) {}

    HotkeyInteraction::Hotkey::~Hotkey() {
        if (interaction)
            delete interaction;
    }

    HotkeyInteraction::HotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint state) : hotkeys(hotkeys), nowHotkeys(nullptr){
        if (this->hotkeys.size() <= state){
            this->hotkeys.resize(state, {});
        }
        nowHotkeys = &this->hotkeys[state];
    }

    HotkeyInteraction::HotkeyInteraction(std::string str) {}

    void HotkeyInteraction::setHotkeyEvent(uint state, HotkeyInteraction::Hotkey* hotkeyEvent) {
        if (hotkeys.size() <= state){
            hotkeys.resize(state, {});
        }
        hotkeys[state].push_back(hotkeyEvent);
    }

    std::vector<HotkeyInteraction::Hotkey*> HotkeyInteraction::getHotkeys(int state) {
        return hotkeys[state];
    }

    HotkeyInteraction::Hotkey* HotkeyInteraction::getHotkey(int state, int i) {
        return hotkeys[state][i];
    }

    void HotkeyInteraction::start(sf::Vector2i mousePosition) {
        for (auto& hotkey : *nowHotkeys) {
            hotkey->interaction->start(mousePosition);
        }
    }

    bool HotkeyInteraction::update(sf::Vector2i mousePosition) {
        for (auto& hotkey : *nowHotkeys) {
            hotkey->interaction->update(mousePosition);
            if (hotkey->interaction->isPress() && hotkey->state != UINT32_MAX){
                finish(mousePosition);
                nowHotkeys = &hotkeys[hotkey->state];
                start(mousePosition);
            }
        }
        return false;
    }

    void HotkeyInteraction::finish(sf::Vector2i mousePosition) {
        for (auto& hotkey : *nowHotkeys) {
            hotkey->interaction->finish(mousePosition);
        }
    }

    HotkeyInteraction *HotkeyInteraction::copy() {
        return new HotkeyInteraction{hotkeys, static_cast<uint>(std::distance(hotkeys.begin(), std::vector<std::vector<Hotkey*>>::iterator(nowHotkeys)))};
    }

    HotkeyInteraction::~HotkeyInteraction() {
        for (auto& hotkeyInteractions : hotkeys) {
            for (auto& hotkey : hotkeyInteractions) {
                delete hotkey;
            }
        }
    }
} // ui