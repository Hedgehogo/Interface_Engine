#include "handleEvent.hpp"

namespace ui {

    void handleEvent(sf::Event event) {
        if(event.type == sf::Event::MouseWheelMoved) {
            MouseWheel::setDelta(event.mouseWheelScroll);
        }
    }

    void clearEvent(){
        MouseWheel::clear();
    }
} // ui