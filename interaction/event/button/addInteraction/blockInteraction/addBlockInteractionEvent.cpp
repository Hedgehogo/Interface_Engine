#include "addBlockInteractionEvent.h"

void ui::AddBlockInteractionEvent::stopPressed(sf::Vector2i mousePosition) {}

ui::AddBlockInteractionEvent::AddBlockInteractionEvent(IInteraction &interaction) : AddInteractionEvent(interaction) {}

ui::AddBlockInteractionEvent *ui::AddBlockInteractionEvent::copy() {
	AddBlockInteractionEvent* addBlockInteractionEvent{new AddBlockInteractionEvent{*interaction}};
	AddInteractionEvent::copy(addBlockInteractionEvent);
	return addBlockInteractionEvent;
}
