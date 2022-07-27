#pragma once

#include "../iScalable/iScalable.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class Interactive : public virtual IUnscalable {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		virtual void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, PanelManager &panelManager) = 0;
		
		void copy(Interactive* interactive);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		explicit Interactive();
	};
}
