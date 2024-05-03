#pragma once

#include "../Event/Event.hpp"
#include "../EventHandler/EventHandler.hpp"

namespace ie {
	class TouchTracker {
	public:
		TouchTracker() = default;
		
		auto collect(event_system::Touch touch) -> bool;
		
		auto reset() -> orl::Option<event_system::Touch>;
	
	private:
		orl::Option<event_system::Touch> touch_;
		bool actual_;
	};
}
