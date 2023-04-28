#pragma once

#include "../iBlockInteraction.hpp"
#include "../../oneKey/oneKeyInteraction.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class PressedInteraction : public OneKeyInteraction, public IBlockInteraction {
	protected:
		InteractionManager* interactionManager;
		
		void copy(PressedInteraction* pressedInteraction);
	
	public:
		PressedInteraction(KeyEvent* event, Key key);
		
		void init(InteractionManager& interactionManager);
		
		void update(sf::Vector2i mousePosition) override;
		
		PressedInteraction* copy();
	};
}
