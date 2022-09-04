#pragma once

#include <SFML/Graphics.hpp>

namespace ui {

    class MouseWheel {
    protected:
        static sf::Vector2f delta;
    public:
        static void setDelta(sf::Event::MouseWheelScrollEvent event);
        static void clear();
        static sf::Vector2f getDelta();
    };

} // ui