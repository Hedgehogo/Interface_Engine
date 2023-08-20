#include "textPressedInteraction.hpp"

#include <utility>
#include "IE/interaction/manager/interactionManager.hpp"
#include "IE/iObject/iUnscalable/interactive/text/interaction/event/textEvent.hpp"

namespace ui {
	TextPressedInteraction::TextPressedInteraction(BoxPtr<KeyEvent>&& event, std::vector<Key> keys, std::vector<Key> blackListKeys) : TextKeysInteraction(std::move(event), std::move(keys), std::move(blackListKeys)) {
	}
	
	void TextPressedInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		this->interactionManager = &textInteractionInitInfo.interactionManager;
		this->text = text;
		dynamic_cast<TextEvent*>(event.get())->init(textInteractionInitInfo);
	}
	
	bool TextPressedInteraction::isBlocked() const {
		return true;
	}
	
	void TextPressedInteraction::update(sf::Vector2i mousePosition) {
		KeysInteraction::update(mousePosition);
		if(!isPress()) {
			interactionManager->deleteInteraction(*this);
		}
	}
	
	TextPressedInteraction* TextPressedInteraction::copy() {
		return new TextPressedInteraction{*this};
	}
}