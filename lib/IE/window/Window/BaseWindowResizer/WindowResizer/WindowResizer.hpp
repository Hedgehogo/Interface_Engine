#pragma once

#include "../BaseWindowResizer.hpp"
#include "IE/enums/KeyHandler/KeyHandler.hpp"
#include <variant>

namespace ie {
	class WindowResizer : public BaseWindowResizer {
	public:
		struct Borders {
			int up = 0, down = 0, left = 0, right = 0;
		};
	
	protected:
		virtual void set_size();
		
		virtual void set_borders();
		
		virtual void get_current_border(int& grip, int*& current_border, int& border, int& border2, int& window_size, int& mouse_position);
	
	public:
		WindowResizer(int internal_border_size = 5, int external_border_size = 5, Key key = Key::MouseLeft);
		
		bool update(sf::Vector2i mouse_position) override;
	
	protected:
		int internal_border_size;
		int external_border_size;
		Key key;
		
		Borders borders;
		sf::Vector2i grip;
		sf::Vector2<int*> current_border;
		bool old_key_pressed;
	};
}