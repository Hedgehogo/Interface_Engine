#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/hotkey/hotkeyInteraction.hpp"
#include "../buttons/textButtonsInteractions.hpp"

namespace ui {

    class TextHotKeyInteraction : public TextInteraction, public HotkeyInteraction{
    public:
        TextHotKeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint state = 0);
        void init(ui::Text *text) override;
        TextHotKeyInteraction * copy() override;

        ~TextHotKeyInteraction() = default;
    };

} // ui