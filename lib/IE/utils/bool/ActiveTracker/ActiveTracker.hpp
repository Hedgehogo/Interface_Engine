#pragma once

namespace ie {
	class ActiveTracker {
	public:
		ActiveTracker() = default;
		
		auto update(bool active) -> void;
		
		auto active() -> bool;
		
		auto stopped() -> bool;
		
		auto started() -> bool;
		
	private:
		bool active_;
		bool old_active_;
	};
}
