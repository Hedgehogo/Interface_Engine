#include "hotkeyInteraction.hpp"

namespace ui {
    HotkeyEvent::HotkeyEvent(ButtonEvent *event) : changeState(false), event(event) {}

    HotkeyEvent::HotkeyEvent(uint state) : changeState(true), state(state) {}
} // ui