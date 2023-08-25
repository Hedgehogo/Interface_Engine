#include "IHidePanelInteraction.hpp"

namespace ui {
	IHidePanelInteraction::IHidePanelInteraction() : IPanelInteraction() {
	}
	
	IBaseInteraction::Priority IHidePanelInteraction::getPriority() const {
		return Priority::lowest;
	}
}

