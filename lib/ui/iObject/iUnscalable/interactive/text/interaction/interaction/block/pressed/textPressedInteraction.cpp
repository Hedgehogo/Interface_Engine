#include "textPressedInteraction.hpp"
#include "ui/interaction/interactionManager/interactionManager.hpp"
#include "ui/iObject/iUnscalable/interactive/text/interaction/event/textEvent.hpp"

namespace ui {
	TextPressedInteraction::TextPressedInteraction(KeyEvent* event, const std::vector<Key> keys, const std::vector<Key> blackListKeys) : TextKeysInteraction(event, keys, blackListKeys) {
	}
	
	void TextPressedInteraction::init(TextInteractionInitInfo textInteractionInitInfo) {
		this->interactionManager = &textInteractionInitInfo.interactionManager;
		this->text = text;
		dynamic_cast<TextEvent*>(event)->init(text);
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
		return new TextPressedInteraction{event->copy(), keys, blackListKeys};
	}
	
}