#include "iInteraction.hpp"

namespace ui {
	bool IInteraction::isBlocked() const {
		return false;
	}
	
	IInteraction::Priority IInteraction::getPriority() const {
		return Priority::medium;
	}
	
	bool IInteraction::operator<(IInteraction &interaction) const {
		return getPriority() < interaction.getPriority();
	}
}
