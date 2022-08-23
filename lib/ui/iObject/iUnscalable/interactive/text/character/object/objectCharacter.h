#pragma once

#include "../baseCharacter.h"
#include "SFML/Graphics.hpp"
#include "../../../../../iObject.hpp"

namespace ui {
    class ObjectCharacter : public BaseCharacter{
        ui::IObject* object;
        std::vector<BaseLine *> lines;
    public:
        ObjectCharacter(ui::IObject* object);

        void setPosition( sf::Vector2f position) override;

        void move(sf::Vector2f position) override;

        std::vector<BaseLine *> & getLine();

        float getHeight() override;

        float getAdvance() override;

        float getKerning(char32_t character) override;

        Special isSpecial() override;

        void draw() override;

        char32_t getChar() override;

        void drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) override;

        ~ObjectCharacter() override;
    };
}