#include "IE/event/KeyHandler/KeyHandler.hpp"

namespace ie {
	template<typename T>
	auto IBasicMouseInteraction<T>::update(sf::Vector2i mouse_position) -> void {
		get_left_button_action().update(mouse_position, KeyHandler{}.is_key_pressed(Key::MouseLeft));
		get_right_button_action().update(mouse_position, KeyHandler{}.is_key_pressed(Key::MouseRight));
	}
}