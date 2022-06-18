#pragma once

#include "SFML/Graphics.hpp"
namespace ui {

    struct TextVariables {
        sf::Color TextColor, textSelectionColor, backgroundSelectionColor;
        sf::Font *font;
        sf::Text::Style style;
        uint size;
    };
}