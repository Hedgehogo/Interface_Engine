#pragma once

#include "../addInteractionEvent.hpp"
#include "../../../../iInteraction/block/iBlockInteraction.hpp"

namespace ui {
	class AddBlockInteractionEvent : public AddInteractionEvent {
	protected:
		void stopPressed() override;
	
	public:
		explicit AddBlockInteractionEvent(IInteraction& interaction);
		
		AddBlockInteractionEvent* copy() override;
	};
}
