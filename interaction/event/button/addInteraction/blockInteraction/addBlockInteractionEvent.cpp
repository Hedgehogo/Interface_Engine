#include "addBlockInteractionEvent.h"

void ui::AddBlockInteractionEvent::stopPressed(sf::Vector2i windowPosition) {}

ui::AddBlockInteractionEvent::AddBlockInteractionEvent(IInteraction &interaction) : AddInteractionEvent(interaction) {}
