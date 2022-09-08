#pragma once

#include "../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui {
    class Text;
    class BaseCharacter;
    class TextEvent : public ButtonEvent_Simple {
    protected:
        Text* text;

        std::vector<BaseCharacter*>::iterator start;
        std::vector<BaseCharacter*>::iterator end;

        void startPressed() override;

        void stopPressed() override;

        void whilePressed() override;

        void whileNotPressed() override;

    public:
        TextEvent(Text &text);

        std::vector<BaseCharacter*>::iterator getStart();
        std::vector<BaseCharacter*>::iterator getEnd();

        std::u32string getSelectionText();

        void setText(Text &text);

        void update(sf::Vector2i mousePosition, bool press) override;

        TextEvent* copy();
    };
}