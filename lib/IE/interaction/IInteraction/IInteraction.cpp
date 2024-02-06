#include "IInteraction.hpp"

namespace ie {
	bool IInteraction::is_blocked() const {
		return false;
	}
	
	IInteraction::Priority IInteraction::get_priority() const {
		return Priority::Medium;
	}
	
	bool IInteraction::operator<(IInteraction& interaction) const {
		return get_priority() < interaction.get_priority();
	}
}
