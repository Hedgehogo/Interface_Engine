#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

using uint = unsigned;

namespace ui {
    struct TextVariables {
        sf::Color TextColor, textSelectionColor, backgroundSelectionColor, inactiveTextSelectionColor, inactiveBackgroundSelectionColor;
        sf::Font *font;
        sf::Text::Style style;
        uint size;
    };
}