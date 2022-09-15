#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/buttons/buttonsInteraction.hpp"

namespace ui {

    class TextButtonsInteraction : public TextInteraction, public ButtonsInteraction{
    public:
        TextButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});

        void init(ui::Text *text) override;

        TextButtonsInteraction * copy() override;

        static TextButtonsInteraction* createFromYaml(const YAML::Node &node);

        ~TextButtonsInteraction() = default;

    };

} // ui