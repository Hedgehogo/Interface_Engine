#pragma once

#include "../iFlat.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IInteractive : public virtual IFlat {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		virtual void init(sf::RenderTarget &renderTarget, PanelManager &panelManager) = 0;
		
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		void copy(IInteractive* iInteractive);
		
	public:
		explicit IInteractive();
	};
}
