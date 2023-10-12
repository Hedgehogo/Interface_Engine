#include "IInteraction.hpp"

namespace ie {
	bool IInteraction::isBlocked() const {
		return false;
	}
	
	IInteraction::Priority IInteraction::getPriority() const {
		return Priority::Medium;
	}
	
	bool IInteraction::operator<(IInteraction& interaction) const {
		return getPriority() < interaction.getPriority();
	}
}
