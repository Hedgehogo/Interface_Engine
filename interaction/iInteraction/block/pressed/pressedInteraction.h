#pragma once
#include "../iBlockInteraction.h"
#include "../../oneButton/oneButtonInteraction.h"
#include "../../../interactionManager/interactionManager.h"

namespace ui {
	class PressedInteraction : public OneButtonInteraction, public IBlockInteraction {
	protected:
		InteractionManager* interactionManager;
	
	public:
		PressedInteraction(ButtonEvent *event, sf::Mouse::Button button);
		
		void init(InteractionManager &interactionManager);
		
		bool update(sf::Vector2i mousePosition) override;
	};
}
