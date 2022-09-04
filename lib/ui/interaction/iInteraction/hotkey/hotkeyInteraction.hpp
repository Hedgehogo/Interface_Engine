#pragma once

#include "../iInteraction.h"
#include <SFML/Graphics.hpp>

namespace ui {
    struct HotkeyEvent{
        bool changeState{false};
        uint state{0};
        ButtonEvent *event{nullptr};
        HotkeyEvent(ButtonEvent *event);
        HotkeyEvent(uint state);
    };

    class HotkeyInteraction : public IInteraction{

    };

} // ui