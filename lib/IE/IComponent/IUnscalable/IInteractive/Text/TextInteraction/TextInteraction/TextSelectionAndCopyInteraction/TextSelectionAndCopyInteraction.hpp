#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextHotkeyInteraction/TextHotkeyInteraction.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextAddBlockInteractionEvent/TextAddBlockInteractionEvent.hpp"
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