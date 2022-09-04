#include "mouseWheel.hpp"

namespace ui {
    sf::Vector2f MouseWheel::delta{};

    void MouseWheel::setDelta(sf::Event::MouseWheelScrollEvent event) {
        if (event.wheel == sf::Mouse::VerticalWheel){
            delta.y += event.delta;
        } else{
            delta.x += event.delta;
        }
    }

    void MouseWheel::clear() {
        delta = {0, 0};
    }

    sf::Vector2f MouseWheel::getDelta() {
        return delta;
    }
}