#pragma once

#include "../textEvent.hpp"
#include "../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"
#include "../../../../../../../modules/appendix/yaml-cpp/yamlBuilder/yamlBuilder.hpp"

namespace ui {

    class TextCopyEvent : public ButtonEvent_Simple, public TextEvent{
    protected:
        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;
    public:
        TextCopyEvent* copy() override;

        ~TextCopyEvent() = default;
    };
	
	bool convertPointer(const YAML::Node &node, TextCopyEvent *&textCopyEvent);

} // ui