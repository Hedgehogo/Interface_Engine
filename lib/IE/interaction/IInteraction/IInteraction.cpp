#include "IInteraction.hpp"

namespace ie {
	auto IInteraction::is_prioritised() const -> bool {
		return false;
	}
	
	auto IInteraction::get_priority() const -> IInteraction::Priority {
		return Priority::Medium;
	}
	
	auto IInteraction::operator<(IInteraction& interaction) const -> bool {
		return get_priority() < interaction.get_priority();
	}
}
