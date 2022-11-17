#include "textSelectionAndCopyInteraction.hpp"

namespace ui {

/*
	std::vector<TextSelectionAndCopyInteraction::Hotkey *> TextSelectionAndCopyInteraction::generateHotkeys(std::vector<AddInteraction> addInteraction, std::vector<TextKeysInteraction *> selectionInteraction) {
		std::vector<TextSelectionAndCopyInteraction::Hotkey *> result{addInteraction.size() + selectionInteraction.size()};

		this->addEvents.resize(addInteraction.size());
		this->pressedInteractions.resize(addInteraction.size());

		for (size_t i = 0; i < addInteraction.size(); ++i) {
			this->pressedInteractions[i] = addInteraction[i].pressedInteraction;
			this->addEvents[i] = new TextAddBlockInteractionEvent{*addInteraction[i].pressedInteraction};

			result[i] = new Hotkey{
				new TextKeysInteraction{
					addEvents[i],
					addInteraction[i].keys,
					addInteraction[i].blackListKeys
				}
			};
		}

		for (size_t i = addInteraction.size(); i < addInteraction.size() + selectionInteraction.size(); ++i) {
			result[i] = new Hotkey{
				selectionInteraction[i]
			};
		}

		return result;
	}
*/

	TextSelectionAndCopyInteraction::TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<TextKeysInteraction *> selectionInteraction) :
		TextHotkeyInteraction({{nullptr}}){
		this->hotkeyStates[0].resize(addInteraction.size() + selectionInteraction.size());

		this->addEvents.resize(addInteraction.size());
		this->pressedInteractions.resize(addInteraction.size());

		for (size_t i = 0; i < addInteraction.size(); ++i) {
			this->pressedInteractions[i] = addInteraction[i].pressedInteraction;
			this->addEvents[i] = new TextAddBlockInteractionEvent{*addInteraction[i].pressedInteraction};

			this->hotkeyStates[0][i] = new Hotkey{
				new TextKeysInteraction{
					addEvents[i],
					addInteraction[i].keys,
					addInteraction[i].blackListKeys
				}
			};
		}

		for (size_t i = addInteraction.size(); i < addInteraction.size() + selectionInteraction.size(); ++i) {
			this->hotkeyStates[0][i] = new Hotkey{
				selectionInteraction[i]
			};
		}

	}

	void TextSelectionAndCopyInteraction::init(Text *text, InteractionManager &interactionManager) {
		TextHotkeyInteraction::init(text, interactionManager);

		for (auto &item: addEvents){
			item->init(text, interactionManager);
		}

		for (const auto &pressedInteraction: pressedInteractions){
			pressedInteraction->init(text, interactionManager);
		}
	}

	TextSelectionAndCopyInteraction *TextSelectionAndCopyInteraction::copy() {
		return nullptr;
	}

	TextSelectionAndCopyInteraction::~TextSelectionAndCopyInteraction() {
		for (auto &item: pressedInteractions){
			delete item;
		}
	}
} // ui