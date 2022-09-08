#pragma once

#include "../iInteraction.hpp"
#include "../buttons/buttonsInteraction.hpp"
#include <SFML/Graphics.hpp>

namespace ui {

    class HotkeyInteraction : public IInteraction{
    public:
        struct Hotkey{
            uint state{UINT32_MAX};
            ButtonsInteraction *interaction{nullptr};
            Hotkey(ButtonsInteraction *interaction, int state = UINT32_MAX);
            Hotkey(uint state);
            ~Hotkey();
        };
    protected:
        std::vector<std::vector<Hotkey*>> hotkeys;
        std::vector<Hotkey*> *nowHotkeys;
    public:
        HotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint state = 0);
        HotkeyInteraction(std::string str);

        void setHotkeyEvent(uint state, Hotkey* hotkeyEvent);

        std::vector<Hotkey*> getHotkeys(int state);

        Hotkey* getHotkey(int state, int i);

        void start(sf::Vector2i mousePosition) override;

        bool update(sf::Vector2i mousePosition) override;

        void finish(sf::Vector2i mousePosition) override;

        HotkeyInteraction* copy() override;

        ~HotkeyInteraction() override;
    };

} // ui