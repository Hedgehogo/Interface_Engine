#include "TouchTracker.hpp"

namespace ie {
	auto TouchTracker::collect(event_system::Touch touch) -> bool {
		return (position_ && id_).map([this, touch](auto value) {
			auto id{std::get<1>(value)};
			if(id == touch.id) {
				position_ = {touch.position};
				return true;
			}
			return false;
		}).some_or_else([this, touch] {
			position_ = {touch.position};
			id_ = {touch.id};
			return true;
		});
	}
	
	auto TouchTracker::reset() -> orl::Option<sf::Vector2i> {
		auto result{(position_ && id_.is_some()).map([this](auto position) {
			return position;
		})};
		position_ = {};
		return result;
	}
}