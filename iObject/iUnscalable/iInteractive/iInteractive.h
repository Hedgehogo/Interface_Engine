#pragma once

#include "../iScalable/iScalable.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class IInteractive : public virtual IUnscalable {
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
