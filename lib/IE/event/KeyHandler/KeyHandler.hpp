#pragma once

#include "IE/enums/Key/Key.hpp"

namespace ie {
	class KeyHandler {
	public:
		KeyHandler() = default;
		
		auto update() -> void;
		
		auto update_keyboard() -> void;
		
		auto update_mouse() -> void;
		
		auto add_key(Key key) -> void;
		
		auto delete_key(Key key) -> void;
		
		auto clear() -> void;
		
		auto is_key_pressed(Key key) const -> bool;
	
	private:
		std::bitset<static_cast<size_t>(Key::MouseWheelRight)> keys_;
	};
	
	auto is_key_pressed(Key key) -> orl::Option<bool>;
}
