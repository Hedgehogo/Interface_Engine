#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/buttons/buttonsInteraction.hpp"

namespace ui {

    class TextButtonsInteractions : public TextInteraction, public ButtonsInteraction{
    public:
        TextButtonsInteractions(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
        void init(ui::Text *text) override;
        TextButtonsInteractions * copy() override;
        ~TextButtonsInteractions() = default;
    };

} // ui