#pragma once

#include "../Event/Event.hpp"
#include "../EventHandler/EventHandler.hpp"

namespace ie {
	class PointerTracker {
	public:
		PointerTracker() = default;
		
		auto collect(EventHandler const& event_handler, event_system::Pointer pointer) -> bool;
		
		auto reset(EventHandler const& event_handler) -> orl::Option<event_system::Pointer>;
		
		auto reset() -> orl::Option<event_system::Pointer>;
	
	private:
		orl::Option<event_system::Pointer> pointer_;
		bool actual_;
	};
}
