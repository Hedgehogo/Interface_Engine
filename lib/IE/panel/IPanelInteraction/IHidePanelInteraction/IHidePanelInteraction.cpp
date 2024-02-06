#include "IHidePanelInteraction.hpp"

namespace ie {
	IBaseInteraction::Priority IHidePanelInteraction::get_priority() const {
		return Priority::Lowest;
	}
}

