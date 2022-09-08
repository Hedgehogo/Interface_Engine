#pragma once
#include "../iBlockInteraction.hpp"
#include "../../oneButton/oneButtonInteraction.hpp"
#include "../../../interactionManager/interactionManager.hpp"

namespace ui {
	class PressedInteraction : public OneButtonInteraction, public IBlockInteraction {
	protected:
		InteractionManager* interactionManager;
		
		void copy(PressedInteraction* pressedInteraction);
	
	public:
		PressedInteraction(ButtonEvent *event, Key button);
		
		void init(InteractionManager &interactionManager);
		
		bool update(sf::Vector2i mousePosition) override;
		
		PressedInteraction* copy();
	};
}
