#include "addBlockInteractionEvent.hpp"

namespace ui {
	void AddBlockInteractionEvent::stopPressed() {
	}
	
	AddBlockInteractionEvent::AddBlockInteractionEvent(IInteraction& interaction) : AddInteractionEvent(interaction) {
	}
	
	AddBlockInteractionEvent* AddBlockInteractionEvent::copy() {
		AddBlockInteractionEvent* addBlockInteractionEvent{new AddBlockInteractionEvent{*interaction}};
		AddInteractionEvent::copy(addBlockInteractionEvent);
		return addBlockInteractionEvent;
	}
}
