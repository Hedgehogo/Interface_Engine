#include "IHidePanelInteraction.hpp"

namespace ie {
	auto IHidePanelInteraction::get_priority() const -> IBaseInteraction::Priority {
		return Priority::Lowest;
	}
}

