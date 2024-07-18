#pragma once

#include "IE/enums/Key/Key.hpp"

namespace ie {
	class KeyHandler {
	public:
		KeyHandler() = default;
		
		auto update() -> void;
		
		auto update_keyboard() -> void;
		
		auto update_mouse() -> void;
		
		auto get_key(Key key) const -> bool;
		
		auto set_key(Key key, bool value) -> void;
		
		auto clear() -> void;
		
	private:
		std::bitset<static_cast<size_t>(Key::MouseWheelRight)> keys_;
	};
	
	auto is_key_pressed(Key key) -> orl::Option<bool>;
}
