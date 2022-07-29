#pragma once

#include "../iScalable/iScalable.h"
#include "../../../interaction/interactionStack/interactionStack.h"

namespace ui {
	class Interactive : public virtual IUnscalable {
	protected:
		InteractionStack* interactionStack;
		InteractionManager* interactionManager;
		
		void copy(Interactive* interactive);
		
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		virtual void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, PanelManager &panelManager) = 0;
		
		explicit Interactive();
	};
}
