#pragma once

#include "../../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui {
    class Switch;
    class SwitchEvent : public ButtonEvent_Simple{
    protected:
        Switch* switcher;

        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;

    public:
        SwitchEvent(Switch& switcher);

        void setSwitcher(Switch& switcher);

        SwitchEvent* copy() override;
    };

}