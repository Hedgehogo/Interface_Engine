#pragma once

#include "../../../../../../../interaction/event/button/simple/buttonEventSimple.h"

namespace ui {
    class Switch;
    class SwitchEvent : public ButtonEvent_Simple{
    protected:
        Switch* switcher;

        void startPressed(sf::Vector2i mousePosition) override;

        void stopPressed (sf::Vector2i mousePosition) override;

        void whilePressed(sf::Vector2i mousePosition) override;

        void whileNotPressed  (sf::Vector2i mousePosition) override;

    public:
        SwitchEvent(Switch& switcher);

        void setSwitcher(Switch& switcher);

        SwitchEvent* copy() override;
    };

}