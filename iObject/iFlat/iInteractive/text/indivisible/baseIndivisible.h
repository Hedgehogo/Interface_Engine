#pragma once

#include "SFML/Graphics.hpp"
#include "../../../../../interaction/iInteraction/iInteraction.h"

namespace ui{
    class BaseTextBlock;
    class BaseIndivisible {
    protected:
        sf::RenderWindow *window;
        BaseTextBlock* parent;
        sf::Vector2f position;
        sf::Vector2f size;
    public:
        enum class special{
            spase,
            enter,
            no
        };


        BaseIndivisible(BaseTextBlock* parent);

        void init(sf::RenderWindow &window);

        void setPosition(const sf::Vector2f &position);

        const sf::Vector2f &getSize() const;

        virtual special isSpecial() = 0;

        virtual void draw() = 0;

    };
}