#pragma once

namespace ie {
	class ActiveTracker {
	public:
		ActiveTracker() = default;
		
		auto update(bool active) -> ActiveTracker&;
		
		auto active() const -> bool;
		
		auto stopped() const -> bool;
		
		auto started() const -> bool;
		
	private:
		bool active_;
		bool old_active_;
	};
}
