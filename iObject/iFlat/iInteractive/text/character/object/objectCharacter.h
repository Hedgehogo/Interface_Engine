#pragma once

#include "../baseCharacter.h"
#include "SFML/Graphics.hpp"
#include "../../../../../iObject.h"

namespace ui {
    class ObjectCharacter : public BaseCharacter{
        ui::IObject* object;
    public:
        ObjectCharacter(ui::IObject* object);

        void setPosition( sf::Vector2f position) override;

        void move(sf::Vector2f position) override;

        float getHeight() override;

        float getAdvance() override;

        float getKerning(wchar_t character) override;

        Special isSpecial() override;

        void draw() override;

        wchar_t getChar() override;

        ~ObjectCharacter() override;
    };
}