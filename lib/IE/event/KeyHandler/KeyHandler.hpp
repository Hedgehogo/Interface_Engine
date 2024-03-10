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
		
		auto clear_global_keys() -> void;
		
		auto to_string(Key key) -> std::string;
		
		auto is_key_pressed(Key key) -> bool;
	
	protected:
		static std::vector<Key> keys_pressed_;
		static std::vector<Key> global_keys_pressed_;
	};
	
	auto is_key_pressed(Key key) -> bool;
}
