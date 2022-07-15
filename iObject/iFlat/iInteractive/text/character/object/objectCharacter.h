#pragma once

#include "../baseCharacter.h"
#include "SFML/Graphics.hpp"
#include "../../../../../iObject.h"

namespace ui {
    class ObjectCharacter : public BaseCharacter{
        ui::IObject* object;
    public:
        ObjectCharacter(ui::IObject* object);

        void setPosition(const sf::Vector2f position);

        void move(sf::Vector2f position);

        float getHeight();

        float getAdvance();

        float getKerning(wchar_t character);

        Special isSpecial();

        void draw();

        wchar_t getChar();

        ~ObjectCharacter() override;
    };
}