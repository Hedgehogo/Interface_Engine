#pragma once

#include "../EventHandler/EventHandler.hpp"

namespace ie {
	struct Touch {
		struct TouchMaker {
			TouchMaker(bool active);
			
			auto operator()(event_system::Pointer pointer) -> Touch;
			
		private:
			bool active_;
		};
		
		static auto from(bool active) -> TouchMaker;
		
		static auto pressing(orl::Option<Touch> touch) -> orl::Option<sf::Vector2i>;
		
		sf::Vector2i position;
		bool active;
	};
}
