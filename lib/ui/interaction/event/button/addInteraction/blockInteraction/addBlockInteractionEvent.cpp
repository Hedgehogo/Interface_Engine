#include "addBlockInteractionEvent.hpp"

void ui::AddBlockInteractionEvent::stopPressed() {}

ui::AddBlockInteractionEvent::AddBlockInteractionEvent(IInteraction &interaction) : AddInteractionEvent(interaction) {}

ui::AddBlockInteractionEvent *ui::AddBlockInteractionEvent::copy() {
	AddBlockInteractionEvent* addBlockInteractionEvent{new AddBlockInteractionEvent{*interaction}};
	AddInteractionEvent::copy(addBlockInteractionEvent);
	return addBlockInteractionEvent;
}
