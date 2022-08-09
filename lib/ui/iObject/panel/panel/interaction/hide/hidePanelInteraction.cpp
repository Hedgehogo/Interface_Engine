#include "hidePanelInteraction.h"

ui::HidePanelInteraction::HidePanelInteraction() : BasePanelInteraction() {}

ui::IInteraction::Priority ui::HidePanelInteraction::getPriority() const {
	return Priority::lowest;
}

