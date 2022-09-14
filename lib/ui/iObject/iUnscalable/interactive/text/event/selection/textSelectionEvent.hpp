#pragma once

#include "../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"
#include "../textEvent.hpp"

namespace ui {
    class BaseCharacter;
    class TextSelectionEvent : public ButtonEvent_Simple, public TextEvent{
    protected:
        std::vector<BaseCharacter*>::iterator start;
        std::vector<BaseCharacter*>::iterator end;

        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;

    public:
        TextSelectionEvent();

        std::vector<BaseCharacter*>::iterator getStart();
        std::vector<BaseCharacter*>::iterator getEnd();

        void update(sf::Vector2i mousePosition, bool press) override;

        TextSelectionEvent* copy();
    };
}