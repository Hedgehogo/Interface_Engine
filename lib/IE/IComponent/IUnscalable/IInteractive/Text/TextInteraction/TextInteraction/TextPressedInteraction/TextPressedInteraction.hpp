#pragma once

#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextAction/TextAction.hpp"
#include "IE/IComponent/IUnscalable/IInteractive/Text/TextInteraction/TextInteraction/TextKeysInteraction/TextKeysInteraction.hpp"

namespace ie {
	class TextPressedInteraction : public TextKeysInteraction {
	public:
		TextPressedInteraction(BoxPtr<TextAction>&& action, std::vector<Key> keys, std::vector<Key> blackListKeys = {});
		
		void init(TextInteractionInitInfo initInfo) override;
		
		bool isBlocked() const override;
		
		void update(sf::Vector2i mousePosition) override;
		
		TextPressedInteraction* copy() override;
	
	protected:
		InteractionManager* interactionManager;
	};
}