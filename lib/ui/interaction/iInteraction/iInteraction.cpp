#include "iInteraction.hpp"

namespace ui {
	IInteraction::IInteraction(bool blocked) : blocked(blocked) {}
	
	bool IInteraction::isBlocked() const {
		return blocked;
	}
	
	IInteraction::Priority IInteraction::getPriority() const {
		return Priority::medium;
	}
	
	bool IInteraction::operator<(IInteraction &interaction) {
		return getPriority() < interaction.getPriority();
	}
}
