#pragma once

#include "../../../../../../interaction/iInteraction/empty/emptyInteraction.hpp"
#include "../textInteraction.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {

    class TextEmptyInteraction : public EmptyInteraction, public TextInteraction{
    public:
        TextEmptyInteraction * copy() override;
    };
	
	bool convertPointer(const YAML::Node &node, TextEmptyInteraction *&textEmptyInteraction);

} // ui