#pragma once

#include "SFML/Graphics.hpp"
#include "../../../../../interaction/interactionManager/interactionManager.h"
#include "../../../../../interaction/interactionStack/interactionStack.h"
#include "../../../../../interaction/iInteraction/iInteraction.h"

namespace ui{
    class BaseTextBlock;
    class BaseCharacter {
    protected:
        sf::RenderWindow *window;
        BaseTextBlock* parent;
        sf::Vector2f position;
        IInteraction *interaction;
    public:
        enum class Special{
            space,
            enter,
            no
        };


        BaseCharacter(BaseTextBlock *parent, IInteraction *interaction);

        void init(sf::RenderWindow &window);

        virtual bool in(sf::Vector2f mousePosition);

        virtual void setPosition(const sf::Vector2f position);

        virtual void move(sf::Vector2f position) = 0;

        const sf::Vector2f &getPosition() const;

        virtual float getHeight() = 0;

        virtual float getAdvance() = 0;

        virtual float getKerning(wchar_t character) = 0;

        virtual Special isSpecial() = 0;

        virtual void draw() = 0;

        virtual wchar_t getChar() = 0;
    };
}