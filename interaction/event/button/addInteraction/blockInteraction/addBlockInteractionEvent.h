#pragma once
#include "../addInteractionEvent.h"
#include "../../../../iInteraction/block/iBlockInteraction.h"

namespace ui {
	class AddBlockInteractionEvent : public AddInteractionEvent {
	protected:
		void stopPressed (sf::Vector2i windowPosition) override;
		
	public:
		explicit AddBlockInteractionEvent(IInteraction &interaction);
		
		AddBlockInteractionEvent* copy() override;
	};
}
