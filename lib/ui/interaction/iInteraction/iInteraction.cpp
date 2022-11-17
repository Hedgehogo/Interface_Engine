#include "iInteraction.hpp"

namespace ui {
	void IInteraction::init(InteractionManager &interactionManager) {}

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
