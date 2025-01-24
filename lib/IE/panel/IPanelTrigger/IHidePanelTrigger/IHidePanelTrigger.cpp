#include "IHidePanelTrigger.hpp"

namespace ie {
	auto IHidePanelTrigger::get_priority() const -> IBaseTrigger::Priority {
		return Priority::Lowest;
	}
}

