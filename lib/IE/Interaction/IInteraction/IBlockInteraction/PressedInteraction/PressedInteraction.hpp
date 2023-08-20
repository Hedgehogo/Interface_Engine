#pragma once

#include "../IBlockInteraction.hpp"
#include "../../OneKeyInteraction/OneKeyInteraction.hpp"
#include "../../../InteractionManager/InteractionManager.hpp"

namespace ui {
	class PressedInteraction : public OneKeyInteraction, public IBlockInteraction {
	public:
		PressedInteraction(BoxPtr<KeyEvent>&& event, Key key);
		
		void init(InteractionInitInfo interactionInitInfo) override;
		
		void update(sf::Vector2i mousePosition) override;
		
		PressedInteraction* copy() override;
	
	protected:
		InteractionManager* interactionManager;
	};
}
