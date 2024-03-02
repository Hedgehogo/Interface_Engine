#include "handle_event.hpp"

#include "../MouseWheel/MouseWheel.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	auto handle_event(sf::Event event) -> void {
		if(event.type == sf::Event::MouseWheelScrolled) {
			MouseWheel::set_delta(event.mouseWheelScroll);
		}
		if(event.type == sf::Event::KeyPressed) {
			KeyHandler::add_key(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::KeyReleased) {
			KeyHandler::delete_key(static_cast<Key>(event.key.code));
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			KeyHandler::add_key(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::MouseLeft)));
		}
		if(event.type == sf::Event::MouseButtonReleased) {
			KeyHandler::delete_key(static_cast<Key>(static_cast<int>(event.mouseButton.button) + static_cast<int>(Key::MouseLeft)));
		}
	}
	
	auto clear_event() -> void {
		MouseWheel::clear();
	}
}