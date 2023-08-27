#include "HandleEvent.hpp"

#include "../MouseWheel/MouseWheel.hpp"
#include "../../Enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	void handleEvent(sf::Event event) {
		if(event.type == sf::Event::MouseWheelScrolled) {
			MouseWheel::setDelta(event.mouseWheelScroll);
		}
		if(event.type == sf::Event::KeyPressed) {
			KeyHandler::addKey(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::KeyReleased) {
			KeyHandler::deleteKey(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			KeyHandler::addKey(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::mouseLeft)));
		}
		if(event.type == sf::Event::MouseButtonReleased) {
			KeyHandler::deleteKey(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::mouseLeft)));
		}
	}
	
	void clearEvent() {
		MouseWheel::clear();
	}
}