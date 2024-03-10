#pragma once

#include "../BaseWindowResizer.hpp"
#include "IE/event/KeyHandler/KeyHandler.hpp"
#include <variant>

namespace ie {
	class WindowResizer : public BaseWindowResizer {
	public:
		struct Borders {
			int up = 0, down = 0, left = 0, right = 0;
		};
	
		WindowResizer(int internal_border_size = 5, int external_border_size = 5, Key key = Key::MouseLeft);
		
		auto update(sf::Vector2i mouse_position, KeyHandler& key_handler) -> bool override;
	
	protected:
		virtual auto set_size() -> void;
		
		virtual auto set_borders() -> void;
		
		virtual auto get_current_border(int& grip, int*& current_border, int& border, int& border2, int& window_size, int& mouse_position) -> void;
		
		int internal_border_size_;
		int external_border_size_;
		Key key_;
		
		Borders borders_;
		sf::Vector2i grip_;
		sf::Vector2<int*> current_border_;
		bool old_key_pressed_;
	};
}