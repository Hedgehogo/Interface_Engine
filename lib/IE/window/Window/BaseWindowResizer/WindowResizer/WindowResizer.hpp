#pragma once

#include "../BaseWindowResizer.hpp"
#include "IE/event/EventHandler/KeyHandler/KeyHandler.hpp"
#include <variant>

namespace ie {
	class WindowResizer : public BaseWindowResizer {
	public:
		struct Borders {
			int up = 0, down = 0, left = 0, right = 0;
		};
		
		WindowResizer(int internal_border_size = 5, int external_border_size = 5, Key key = Key::MouseLeft);
		
		auto update(std::vector<Event> const& events, EventHandler& event_handler) -> bool override;
	
	protected:
		int internal_border_size_;
		int external_border_size_;
		Key key_;
		
		Borders borders_;
		sf::Vector2i grip_;
		sf::Vector2<orl::Option<int*> > current_borders_;
		bool old_key_pressed_;
	};
}