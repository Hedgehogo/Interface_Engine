#pragma once

#include "IE/iObject/iUnscalable/interactive/text/interaction/interaction/keys/textKeysInteraction.hpp"

namespace ui {
	class TextPressedInteraction : public TextKeysInteraction {
	public:
		TextPressedInteraction(BoxPtr<KeyEvent> && event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		void init(TextInteractionInitInfo textInteractionInitInfo) override;
		
		bool isBlocked() const override;
		
		void update(sf::Vector2i mousePosition) override;
		
		TextPressedInteraction* copy() override;
	
	protected:
		InteractionManager* interactionManager;
	};
}