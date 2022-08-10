#pragma once
#include "../basePanel.h"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, UpdateManager &updateManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		ConstPanel(IScalable *object, BaseSizing2 *sizing, BasePositioning2 *positioning, bool displayed = false);
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
}
