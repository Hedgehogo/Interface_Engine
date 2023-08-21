#include "TextSelectionAndCopyInteraction.hpp"
#include "IE/IComponent/IComponent.hpp"

namespace ui {
	TextSelectionAndCopyInteraction::TextSelectionAndCopyInteraction(std::vector<AddInteraction> addInteraction, std::vector<BoxPtr<TextKeysInteraction>>&& selectionInteraction) :
		TextHotkeyInteraction(std::vector<std::vector<BoxPtr<Hotkey> > >{{}}) {
		this->hotkeyStates[0].resize(addInteraction.size() + selectionInteraction.size());
		
		this->addEvents.resize(addInteraction.size());
		this->pressedInteractions.resize(addInteraction.size());
		
		for(size_t i = 0; i < addInteraction.size(); ++i) {
			this->pressedInteractions[i] = BoxPtr < TextInteraction > {addInteraction[i].pressedInteraction};
			this->addEvents[i] = new TextAddBlockInteractionEvent{*addInteraction[i].pressedInteraction};
			
			this->hotkeyStates[0][i] = makeBoxPtr<Hotkey>(
				makeBoxPtr<KeysInteraction, TextKeysInteraction>(
					BoxPtr<KeyEvent>{addEvents[i]},
					addInteraction[i].keys,
					addInteraction[i].blackListKeys
				)
			);
		}
		
		for(size_t i = addInteraction.size(); i < addInteraction.size() + selectionInteraction.size(); ++i) {
			this->hotkeyStates[0][i] = makeBoxPtr<Hotkey>(
				dynamicCast<ui::KeysInteraction>(std::move(selectionInteraction[i]))
			);
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
	
	TextSelectionAndCopyInteraction* TextSelectionAndCopyInteraction::copy() {
		TextSelectionAndCopyInteraction* textSelectionAndCopyInteraction{new TextSelectionAndCopyInteraction{*this}};
		TextInteraction::copy(textSelectionAndCopyInteraction);
		return textSelectionAndCopyInteraction;
	}
}