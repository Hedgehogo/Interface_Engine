#pragma once

#include "../textEvent.hpp"
#include "../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui {

    class TextCopyEvent : public ButtonEvent_Simple, public TextEvent{
    protected:
        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;
    public:
        TextCopyEvent* copy() override;

        static TextCopyEvent* createFromYaml(const YAML::Node &node);

        ~TextCopyEvent() = default;
    };

} // ui