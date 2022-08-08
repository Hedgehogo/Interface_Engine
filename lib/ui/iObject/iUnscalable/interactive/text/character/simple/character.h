#pragma once
#include "../baseCharacter.h"

#include <string>

#include "SFML/Graphics.hpp"

#include "../../textVariables.h"

namespace ui{
    class Character : public BaseCharacter{
    protected:

        sf::RenderTarget* renderTarget;

        wchar_t character;

        sf::Glyph glyph;
        TextVariables &textVariables;
        sf::VertexArray vertexArray;
        sf::Texture texture;
        sf::Vector2f origin;
    public:
        Character(wchar_t character, TextVariables &textVariables);

        void init(sf::RenderTarget &renderTarget) override;

        void draw() override;

        void move(sf::Vector2f position);

        bool in(sf::Vector2f mousePosition) override;

        float getHeight() override;

        float getAdvance() override;

        float getKerning(wchar_t character) override;

        Special isSpecial() override;

        wchar_t getChar() override;

        void setPosition(const sf::Vector2f position);

    private:
        static bool debug;
		
    public:
        static void setDebug(bool debug);
		
        void drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) override;
    };
}