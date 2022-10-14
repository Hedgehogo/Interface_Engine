#include "handleEvent.hpp"

#include "../mouseWheel/mouseWheel.hpp"
#include "../../enums/keyHandler/keyHandler.hpp"

namespace ui {

    void handleEvent(sf::Event event) {
        if(event.type == sf::Event::MouseWheelMoved){
            MouseWheel::setDelta(event.mouseWheelScroll);
        }
        if (event.type == sf::Event::KeyPressed){
            KeyHandler::addKey(static_cast<KeyHandler::Key>(event.key.code));
        }
        if (event.type == sf::Event::KeyReleased){
            KeyHandler::deleteKey(static_cast<KeyHandler::Key>(event.key.code));
        }
        if (event.type == sf::Event::MouseButtonPressed){
            KeyHandler::addKey(static_cast<KeyHandler::Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(KeyHandler::Key::mouseLeft)));
        }
        if (event.type == sf::Event::MouseButtonReleased){
            KeyHandler::deleteKey(static_cast<KeyHandler::Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(KeyHandler::Key::mouseLeft)));
        }
    }

    void clearEvent(){
        MouseWheel::clear();
    }
} // ui