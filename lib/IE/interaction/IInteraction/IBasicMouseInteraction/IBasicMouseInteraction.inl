#include "IE/enums/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	void IBasicMouseInteraction<T>::update(sf::Vector2i mouse_position) {
		get_left_button_action().update(mouse_position, KeyHandler::is_key_pressed(Key::MouseLeft));
		get_right_button_action().update(mouse_position, KeyHandler::is_key_pressed(Key::MouseRight));
	}
}