#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/hotkey/hotkeyInteraction.hpp"
#include "../buttons/textButtonsInteraction.hpp"

namespace ui {

    class TextHotkeyInteraction : public TextInteraction, public HotkeyInteraction{
    public:
        TextHotkeyInteraction(std::vector<std::vector<Hotkey*>> hotkeys, uint startState = 0);
        void init(Text *text) override;
        TextHotkeyInteraction * copy() override;

        static TextHotkeyInteraction* createFromYaml(const YAML::Node &node);

        ~TextHotkeyInteraction() = default;
    };

} // ui