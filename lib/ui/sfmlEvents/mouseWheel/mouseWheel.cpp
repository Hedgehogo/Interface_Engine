#include "mouseWheel.hpp"

namespace ui {
    sf::Vector2f MouseWheel::delta{0, 0};

    void MouseWheel::setDelta(sf::Event::MouseWheelScrollEvent event) {
        if (event.wheel == sf::Mouse::HorizontalWheel){
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