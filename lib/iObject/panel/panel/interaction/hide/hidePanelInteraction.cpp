#include "hidePanelInteraction.h"

ui::HidePanelInteraction::HidePanelInteraction() : BasePanelInteraction() {}

ui::InteractionType ui::HidePanelInteraction::getType() const {
	return ui::InteractionType::hidePanel;
}

