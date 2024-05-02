#pragma once

#include "../Event/Event.hpp"

namespace ie {
	class TouchTracker {
	public:
		TouchTracker() = default;
		
		auto collect(event_system::Touch touch) -> bool;
		
		auto reset() -> orl::Option<sf::Vector2i>;
	
	private:
		orl::Option<size_t> id_;
		orl::Option<sf::Vector2i> position_;
	};
}
