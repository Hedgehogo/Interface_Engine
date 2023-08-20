#pragma once

#include "IE/iObject/iUnscalable/interactive/text/Interaction/Interaction/hotKeys/textHotkeyInteraction.hpp"
#include "IE/iObject/iUnscalable/interactive/text/Interaction/event/addBlockInteraction/textAddBlockInteractionEvent.hpp"
#include <vector>

namespace ui {
	class TextSelectionAndCopyInteraction : public TextHotkeyInteraction {
	public:
		struct AddInteraction {
			TextInteraction* pressedInteraction;
			std::vector<Key> keys;
			std::vector<Key> blackListKeys = {};
		};
		
		TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<BoxPtr<TextKeysInteraction>> && selectionInteraction = {});
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
		TextSelectionAndCopyInteraction* copy() override;
	
	protected:
		std::vector<TextAddBlockInteractionEvent*> addEvents;
		std::vector<BoxPtr<TextInteraction>> pressedInteractions;
	};
}