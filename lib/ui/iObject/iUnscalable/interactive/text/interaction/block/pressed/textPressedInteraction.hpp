#pragma once

#include "../../keys/textKeysInteraction.hpp"

namespace ui {
	class TextPressedInteraction : public TextKeysInteraction {
	protected:
		InteractionManager* interactionManager;
	public:
		TextPressedInteraction(KeyEvent* event, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		void init(Text* text, InteractionManager& interactionManager) override;
		
		bool isBlocked() const override;
		
		void update(sf::Vector2i mousePosition) override;
		
		TextPressedInteraction* copy() override;
	};
}