#include "ActiveTracker.hpp"

namespace ie {
	auto ActiveTracker::update(bool active) -> void {
		old_active_ = active_;
		active_ = active;
	}
	
	auto ActiveTracker::active() -> bool {
		return active_;
	}
	
	auto ActiveTracker::stopped() -> bool {
		return !active_ && old_active_;
	}
	
	auto ActiveTracker::started() -> bool {
		return active_ && !old_active_;
	}
}