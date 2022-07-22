#include "iInteraction.h"

ui::IInteraction::IInteraction(bool blocked) : blocked(blocked) {}

bool ui::IInteraction::isBlocked() const {
	return blocked;
}

ui::InteractionType ui::IInteraction::getType() const {
	return InteractionType::general;
}
