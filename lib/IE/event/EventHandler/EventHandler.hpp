#pragma once

#include "../Event/Event.hpp"
#include "../KeyHandler/KeyHandler.hpp"

namespace ie {
	class EventHandler {
	public:
		template<typename K, typename V>
		using Map = absl::flat_hash_map<K, V>;
		
		EventHandler() = default;
		
		auto key_handler() -> KeyHandler&;
		
		auto key_handler() const -> KeyHandler const&;
		
		auto get_key(Key key) -> bool;
		
		auto set_key(Key key, bool value) -> void;
		
		auto get_scroll() -> sf::Vector2f;
		
		auto set_scroll(size_t id, float value) -> void;
		
		auto get_touch(size_t id) -> orl::Option<sf::Vector2i>;
		
		auto set_touch(size_t id, sf::Vector2i value) -> void;
		
		auto move_window_position(sf::Vector2i position) -> void;
		
		auto remove_touch(size_t id) -> void;
		
		auto get_joystick_button(size_t id, size_t button_id) -> bool;
		
		auto set_joystick_button(size_t id, size_t button_id, bool value) -> void;
		
		auto update() -> void;
		
		auto poll_events(std::vector<Event>& events) -> void;
		
	private:
		KeyHandler key_handler_;
		std::array<float, 2> scroll_;
		Map<size_t, sf::Vector2i> touch_;
		Map<size_t, Map<size_t, bool> > joystick_buttons_;
	};
}
