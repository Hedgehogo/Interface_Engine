#pragma once

#include "../IInteraction.hpp"

namespace ie {
	class IPrioritisedInteraction : public virtual IInteraction {
	public:
		auto is_prioritised() const -> bool override;
		
		virtual auto handle_event_prioritised(Event event) -> bool = 0;
	};
}
