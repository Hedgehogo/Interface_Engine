#include "ActiveTracker.hpp"

namespace ie {
	auto ActiveTracker::update(bool active) -> ActiveTracker& {
		old_active_ = active_;
		active_ = active;
		return *this;
	}
	
	auto ActiveTracker::active() const -> bool {
		return active_;
	}
	
	auto ActiveTracker::stopped() const -> bool {
		return !active_ && old_active_;
	}
	
	auto ActiveTracker::started() const -> bool {
		return active_ && !old_active_;
	}
}