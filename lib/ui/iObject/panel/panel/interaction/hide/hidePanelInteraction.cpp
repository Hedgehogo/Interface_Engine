#include "hidePanelInteraction.hpp"

namespace ui {
	HidePanelInteraction::HidePanelInteraction() : BasePanelInteraction() {
	}
	
	IInteraction::Priority HidePanelInteraction::getPriority() const {
		return Priority::lowest;
	}
}

