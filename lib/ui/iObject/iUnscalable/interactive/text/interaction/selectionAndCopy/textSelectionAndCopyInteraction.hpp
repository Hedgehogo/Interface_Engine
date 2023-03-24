#pragma once

#include "../hotKeys/textHotkeyInteraction.hpp"
#include "../../event/addBlockInteraction/textAddBlockInteractionEvent.hpp"
#include <vector>

namespace ui {
	class TextSelectionAndCopyInteraction : public TextHotkeyInteraction{
	public:
		struct AddInteraction{
			TextInteraction * pressedInteraction;
			std::vector<Key> keys;
			std::vector<Key> blackListKeys = {};
		};
	protected:
		std::vector<ui::TextAddBlockInteractionEvent *> addEvents;
		std::vector<ui::TextInteraction *> pressedInteractions;

	public:
		TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<TextKeysInteraction *> selectionInteraction = {});

		void init(Text *text, InteractionManager &interactionManager) override;

		TextSelectionAndCopyInteraction *copy() override;

		~TextSelectionAndCopyInteraction();
	};
}