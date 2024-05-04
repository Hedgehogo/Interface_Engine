#include "TouchTracker.hpp"

namespace ie {
	auto TouchTracker::collect(EventHandler const& event_handler, event_system::Touch touch) -> bool {
		bool result = touch_.map([this, &event_handler, touch](event_system::Touch value) {
			return !actual_ && (event_handler.get_touch(value.id).is_some() == (touch.id == value.id));
		}).some_or(true);
		if(result) {
			touch_ = touch;
			actual_ = true;
		}
		return result;
	}
	
	auto TouchTracker::reset(EventHandler const& event_handler) -> orl::Option<event_system::Touch> {
		return touch_.and_then([&event_handler](event_system::Touch value) {
			return event_handler.get_touch(value.id).map([value](sf::Vector2i position) {
				return event_system::Touch{value.id, position};
			});
		});
	}
	
	auto TouchTracker::reset() -> orl::Option<event_system::Touch> {
		if(actual_) {
			actual_ = false;
			return touch_;
		}
		return {};
	}
}