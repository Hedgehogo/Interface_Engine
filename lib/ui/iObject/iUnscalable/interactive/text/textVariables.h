#pragma once

#include "SFML/Graphics.hpp"

typedef unsigned uint;

namespace ui {
    struct TextVariables {
        sf::Color TextColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor;
        sf::Font *font;
        sf::Text::Style style;
        uint size;
    };
}