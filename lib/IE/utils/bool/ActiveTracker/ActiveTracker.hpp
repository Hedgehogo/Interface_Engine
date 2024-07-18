#pragma once

namespace ie {
	class ActiveTracker {
	public:
		ActiveTracker();
		
		auto update(bool active) -> ActiveTracker&;
		
		auto active() const -> bool;
		
		auto changed() const -> bool;
		
		auto started() const -> bool;
		
		auto stopped() const -> bool;
		
	private:
		bool active_;
		bool old_active_;
	};
}
