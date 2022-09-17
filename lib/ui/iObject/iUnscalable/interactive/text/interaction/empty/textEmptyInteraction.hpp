#pragma once

#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"
#include "../textInteraction.hpp"

namespace ui {

    class TextEmptyInteraction : public EmptyInteraction, public TextInteraction{
    public:
        TextEmptyInteraction * copy() override;

        static TextEmptyInteraction* createFromYaml(const YAML::Node &node);
    };

} // ui