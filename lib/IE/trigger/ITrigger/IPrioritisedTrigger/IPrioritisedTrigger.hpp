#pragma once

#include "../ITrigger.hpp"

namespace ie {
	class IPrioritisedTrigger : public virtual ITrigger {
	public:
		auto is_prioritised() const -> bool override;
		
		virtual auto handle_event_prioritised(Event event) -> bool = 0;
	};
}
