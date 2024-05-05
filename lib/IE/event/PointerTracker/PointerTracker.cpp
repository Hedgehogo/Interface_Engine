#include "PointerTracker.hpp"

namespace ie {
	auto PointerTracker::collect(EventHandler const& event_handler, event_system::Pointer pointer) -> bool {
		bool result = pointer_.map([this, &event_handler, pointer](event_system::Pointer value) {
			return !actual_ && (event_handler.get_pointer(value.id).is_some() == (pointer.id == value.id));
		}).some_or(true);
		if(result) {
			pointer_ = pointer;
			actual_ = true;
		}
		return result;
	}
	
	auto PointerTracker::reset(EventHandler const& event_handler) -> orl::Option<event_system::Pointer> {
		return pointer_.and_then([&event_handler](event_system::Pointer value) {
			return event_handler.get_pointer(value.id).map([value](sf::Vector2i position) {
				return event_system::Pointer{value.id, position};
			});
		});
	}
	
	auto PointerTracker::reset() -> orl::Option<event_system::Pointer> {
		if(actual_) {
			actual_ = false;
			return pointer_;
		}
		return {};
	}
}