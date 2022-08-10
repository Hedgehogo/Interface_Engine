#include "iInteraction.h"

namespace ui {
	IInteraction::IInteraction(bool blocked) : blocked(blocked) {}
	
	bool IInteraction::isBlocked() const {
		return blocked;
	}
	
	IInteraction::Priority IInteraction::getPriority() const {
		return Priority::medium;
	}
	
	bool IInteraction::operator<(ui::IInteraction &interaction) {
		return getPriority() < interaction.getPriority();
	}

    IInteraction *IInteraction::createFromYaml(const YAML::Node &node) {
        return nullptr;
    }
}
