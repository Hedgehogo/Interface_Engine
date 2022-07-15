#pragma once
#include "../baseCharacter.h"

#include <string>

#include "SFML/Graphics.hpp"

#include "../../textVariables.h"

namespace ui{
    class Character : public BaseCharacter{
    protected:
        wchar_t character;

        sf::Glyph glyph;
        TextVariables &textVariables;
        sf::Sprite sprite;
    public:
        Character(wchar_t character, TextVariables &textVariables);

        void draw() override;

        void move(sf::Vector2f position);

        bool in(sf::Vector2f mousePosition) override;

        float getHeight() override;

        float getAdvance() override;

        float getKerning(wchar_t character) override;

        Special isSpecial() override;

        wchar_t getChar() override;

        void setPosition(const sf::Vector2f position);
    };
}