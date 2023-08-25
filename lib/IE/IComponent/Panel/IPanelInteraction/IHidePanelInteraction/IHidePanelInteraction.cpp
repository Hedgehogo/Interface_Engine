#include "IHidePanelInteraction.hpp"

namespace ui {
	IBaseInteraction::Priority IHidePanelInteraction::getPriority() const {
		return Priority::lowest;
	}
}

