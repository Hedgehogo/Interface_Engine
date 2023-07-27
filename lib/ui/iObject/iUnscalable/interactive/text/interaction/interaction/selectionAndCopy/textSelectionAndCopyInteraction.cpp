#include "textSelectionAndCopyInteraction.hpp"
#include "ui/iObject/iObject.hpp"

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
	
	TextSelectionAndCopyInteraction::TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<TextKeysInteraction*> selectionInteraction) :
		TextHotkeyInteraction({{nullptr}}) {
		this->hotkeyStates[0].resize(addInteraction.size() + selectionInteraction.size());
		
		this->addEvents.resize(addInteraction.size());
		this->pressedInteractions.resize(addInteraction.size());
		
		for(size_t i = 0; i < addInteraction.size(); ++i) {
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
		
		for(size_t i = addInteraction.size(); i < addInteraction.size() + selectionInteraction.size(); ++i) {
			this->hotkeyStates[0][i] = new Hotkey{
				selectionInteraction[i]
			};
		}
		
	}
	
	void TextSelectionAndCopyInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		TextHotkeyInteraction::init(textInteractionInitInfo);
		
		for(auto& item: addEvents) {
			item->init(textInteractionInitInfo);
		}
		
		for(const auto& pressedInteraction: pressedInteractions) {
			pressedInteraction->init(textInteractionInitInfo);
		}
	}
	
	TextSelectionAndCopyInteraction::TextSelectionAndCopyInteraction(
		const std::vector<std::vector<Hotkey*>>& hotkeys, uint startState, const std::vector<ui::TextAddBlockInteractionEvent*>& addEvents,
		const std::vector<ui::TextInteraction*>& pressedInteractions) : TextHotkeyInteraction(hotkeys, startState), addEvents(addEvents), pressedInteractions(pressedInteractions) {
	}
	
	TextSelectionAndCopyInteraction* TextSelectionAndCopyInteraction::copy() {
		std::vector<std::vector<Hotkey*>> hotkeysCopy(hotkeyStates.size());
		for(int i = 0; i < hotkeysCopy.size(); ++i) {
			hotkeysCopy[i].resize( hotkeyStates[i].size());
			for(int j = 0; j < hotkeysCopy[i].size(); ++j) {
				hotkeysCopy[i][j] = new Hotkey{hotkeyStates[i][j]->interaction->copy(), hotkeyStates[i][j]->state};
			}
		}
		
		uint startState = 0;
		for(int i = 0; i < hotkeyStates.size(); ++i) {
			if (&hotkeyStates[i] == nowHotkeys) startState = i;
		}

		auto textSelectionAndCopyInteraction{new TextSelectionAndCopyInteraction{hotkeysCopy, startState, ui::copy(addEvents), ui::copy(pressedInteractions)}};
		TextInteraction::copy(textSelectionAndCopyInteraction);
		return textSelectionAndCopyInteraction;
	}
	
	TextSelectionAndCopyInteraction::~TextSelectionAndCopyInteraction() {
		for(auto& item: pressedInteractions) {
			delete item;
		}
	}
}