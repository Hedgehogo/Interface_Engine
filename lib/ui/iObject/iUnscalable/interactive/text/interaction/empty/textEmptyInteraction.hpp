#pragma once

#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"
#include "../textInteraction.hpp"

namespace ui {

    class TextEmptyInteraction : public EmptyInteraction, public TextInteraction{
    public:
        TextEmptyInteraction * copy() override;
    };

} // ui