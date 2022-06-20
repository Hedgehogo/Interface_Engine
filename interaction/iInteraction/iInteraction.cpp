#include "iInteraction.h"

ui::IInteraction::IInteraction(bool blocked) : blocked(blocked) {}

bool ui::IInteraction::isBlocked() const {
	return blocked;
}