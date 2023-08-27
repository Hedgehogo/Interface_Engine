#include "TextPressedInteraction.hpp"

#include <utility>
#include "IE/Interaction/InteractionManager/InteractionManager.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextEvent/TextEvent.hpp"

namespace ie {
	TextPressedInteraction::TextPressedInteraction(BoxPtr<TextEvent>&& event, std::vector<Key> keys, std::vector<Key> blackListKeys) :
		TextKeysInteraction(std::move(event), std::move(keys), std::move(blackListKeys)) {
	}
	
	void TextPressedInteraction::init(TextInteractionInitInfo initInfo) {
		this->interactionManager = &initInfo.interactionManager;
		dynamic_cast<TextEvent&>(*event).init(initInfo);
	}
	
	bool TextPressedInteraction::isBlocked() const {
		return true;
	}
	
	void TextPressedInteraction::update(sf::Vector2i mousePosition) {
		TextKeysInteraction::update(mousePosition);
		if(!isPress()) {
			interactionManager->deleteInteraction(*this);
		}
	}
	
	TextPressedInteraction* TextPressedInteraction::copy() {
		return new TextPressedInteraction{*this};
	}
}