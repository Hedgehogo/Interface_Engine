#pragma once

#include "../Event/Event.hpp"
#include "../EventHandler/EventHandler.hpp"

namespace ie {
	class TouchTracker {
	public:
		TouchTracker() = default;
		
		auto collect(EventHandler const& event_handler, event_system::Touch touch) -> bool;
		
		auto reset(EventHandler const& event_handler) -> orl::Option<event_system::Touch>;
		
		auto reset() -> orl::Option<event_system::Touch>;
	
	private:
		orl::Option<event_system::Touch> touch_;
		bool actual_;
	};
}
