#pragma once

#include "../iFlat.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IInteractive : public IFlat {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		virtual void init(sf::RenderWindow &window, Panel *parent, PanelManager &overlayStack) = 0;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, Panel *parent, PanelManager &overlayStack) override;
		
		void copy(IInteractive* iInteractive);
		
	public:
		explicit IInteractive();
	};
}
