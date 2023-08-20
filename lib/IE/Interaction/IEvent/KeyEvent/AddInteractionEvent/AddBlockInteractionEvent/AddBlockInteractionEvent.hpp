#pragma once

#include "../AddInteractionEvent.hpp"
#include "../../../../IInteraction/IBlockInteraction/IBlockInteraction.hpp"

namespace ui {
	class AddBlockInteractionEvent : public AddInteractionEvent {
	protected:
		void stopPressed() override;
	
	public:
		explicit AddBlockInteractionEvent(IInteraction& interaction);
		
		AddBlockInteractionEvent* copy() override;
	};
}
