#pragma once

#include "../iBlockInteraction.hpp"
#include "../../oneKey/oneKeyInteraction.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class PressedInteraction : public OneKeyInteraction, public IBlockInteraction {
	protected:
		void copy(PressedInteraction* pressedInteraction);
	
	public:
		PressedInteraction(KeyEvent* event, Key key);
		
		void init(InteractionInitInfo interactionInitInfo);
		
		void update(sf::Vector2i mousePosition) override;
		
		PressedInteraction* copy();
	
	protected:
		InteractionManager* interactionManager;
	};
}
