#pragma once

#include "SFML/Graphics.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../../interaction/iInteraction/iInteraction.h"
#include "../line/baseLine.h"

typedef unsigned uint;

namespace ui{
    class BaseTextBlock;
    class BaseCharacter {
    protected:
        sf::Vector2f position;
    public:
        enum class Special{
            space,
            enter,
            no
        };
        BaseCharacter();

        virtual void init(sf::RenderTarget &renderTarget);

        virtual bool in(sf::Vector2f mousePosition);

        virtual void setPosition(sf::Vector2f position);

        virtual void move(sf::Vector2f position);

        virtual std::vector<BaseLine *> & getLine() = 0;

        const sf::Vector2f &getPosition() const;

        virtual float getHeight() = 0;

        virtual float getAdvance() = 0;

        virtual float getKerning(wchar_t character) = 0;

        virtual bool isEnter();

        virtual Special isSpecial() = 0;

        virtual void draw() = 0;

        virtual wchar_t getChar() = 0;

        virtual void drawDebug(sf::RenderTarget &renderTarget, int indentAddition, uint hue, uint hueOffset) = 0;

        virtual ~BaseCharacter() = default;
    };
}