#pragma once

#include "ui/iObject/iUnscalable/interactive/text/interaction/interaction/hotKeys/textHotkeyInteraction.hpp"
#include "ui/iObject/iUnscalable/interactive/text/interaction/event/addBlockInteraction/textAddBlockInteractionEvent.hpp"
#include <vector>

namespace ui {
	class TextSelectionAndCopyInteraction : public TextHotkeyInteraction {
	public:
		struct AddInteraction {
			TextInteraction* pressedInteraction;
			std::vector<Key> keys;
			std::vector<Key> blackListKeys = {};
		};
		
	protected:
		std::vector<ui::TextAddBlockInteractionEvent*> addEvents;
		std::vector<ui::TextInteraction*> pressedInteractions;
	
	public:
		TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<TextKeysInteraction*> selectionInteraction = {});
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
	protected:
		TextSelectionAndCopyInteraction(const std::vector<std::vector<Hotkey*>>& hotkeys, uint startState, const std::vector<ui::TextAddBlockInteractionEvent*>& addEvents, const std::vector<ui::TextInteraction*>& pressedInteractions);
	
	public:
		TextSelectionAndCopyInteraction* copy() override;
		
		~TextSelectionAndCopyInteraction();
	};
}