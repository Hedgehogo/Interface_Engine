#pragma once

#include "../iFlat.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IInteractive : public virtual IFlat {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		virtual void init(sf::RenderWindow &window, PanelManager &panelManager) = 0;
		
		void init(sf::RenderWindow &window, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(IInteractive* iInteractive);
		
	public:
		explicit IInteractive();
	};
}
