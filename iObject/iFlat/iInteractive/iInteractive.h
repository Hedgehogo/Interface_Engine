#pragma once

#include "../iFlat.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IInteractive : public IFlat {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		virtual void init(sf::RenderWindow &window, Panel *parent, PanelStack &overlayStack) = 0;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelStack &overlayStack) override;
		
	public:
		explicit IInteractive();
	};
}
