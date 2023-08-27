#include "IHidePanelInteraction.hpp"

namespace ie {
	IBaseInteraction::Priority IHidePanelInteraction::getPriority() const {
		return Priority::lowest;
	}
}

