#pragma once

#include "../textInteraction.hpp"
#include "../../../../../../interaction/iInteraction/buttons/buttonsInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {

    class TextButtonsInteraction : public TextInteraction, public ButtonsInteraction{
    public:
        TextButtonsInteraction(ButtonEvent *event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});

        void init(Text *text) override;

        TextButtonsInteraction * copy() override;

        ~TextButtonsInteraction() = default;

    };
	
	bool convertPointer(const YAML::Node &node, TextButtonsInteraction *&textButtonsInteraction);

} // ui