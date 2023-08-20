#include "addBlockInteractionEvent.hpp"

namespace ui {
	void AddBlockInteractionEvent::stopPressed() {
	}
	
	AddBlockInteractionEvent::AddBlockInteractionEvent(IInteraction& interaction) : AddInteractionEvent(interaction) {
	}
	
	AddBlockInteractionEvent* AddBlockInteractionEvent::copy() {
		return new AddBlockInteractionEvent{*this};
	}
}
