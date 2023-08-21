#include "IHidePanelInteraction.hpp"

namespace ui {
	IHidePanelInteraction::IHidePanelInteraction() : IPanelInteraction() {
	}
	
	IInteraction::Priority IHidePanelInteraction::getPriority() const {
		return Priority::lowest;
	}
}

