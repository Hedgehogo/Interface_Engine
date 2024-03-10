#pragma once

#include "IE/enums/Key/Key.hpp"

namespace ie {
	class KeyHandler {
	public:
		static auto get_keys_pressed() -> std::vector<Key>;
		
		static auto set_keys_pressed(std::vector<Key> keys_pressed) -> void;
		
		static auto update() -> void;
		
		static auto update_keyboard() -> void;
		
		static auto update_mouse() -> void;
		
		static auto add_key(Key key) -> void;
		
		static auto delete_key(Key key) -> void;
		
		static auto clear() -> void;
		
		static auto clear_global_keys() -> void;
		
		static auto to_string(Key key) -> std::string;
		
		static auto is_key_pressed(Key key) -> bool;
	
	protected:
		static std::vector<Key> keys_pressed_;
		static std::vector<Key> global_keys_pressed_;
	};
	
	auto is_key_pressed(Key key) -> bool;
}
