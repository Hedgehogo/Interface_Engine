#pragma once
#include "../baseIndivisible.h"

#include <string>

#include "SFML/Graphics.hpp"

namespace ui{
    class Indivisible : public BaseIndivisible{
    protected:
        sf::Text text;
    public:
        Indivisible(sf::Text text, BaseTextBlock* parent);
        void draw() override;

        special isSpecial();
    };
}