#include "TouchTracker.hpp"

namespace ie {
	auto TouchTracker::collect(event_system::Touch touch) -> bool {
		return !actual_ && touch_.map([this, touch](auto value) {
			if(value.id == touch.id) {
				touch_ = {touch};
				actual_ = true;
				return true;
			}
			return false;
		}).some_or_else([this, touch] {
			touch_ = {touch};
			actual_ = true;
			return true;
		});
	}
	
	auto TouchTracker::reset() -> orl::Option<event_system::Touch> {
		if(actual_) {
			actual_ = false;
			return touch_;
		}
		touch_ = {};
		return {};
	}
}