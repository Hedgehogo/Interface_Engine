#pragma once
#include "../basePanel.h"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		void init(sf::RenderTarget &renderTarget, DrawManager &drawManager, InteractionManager &interactionManager, InteractionStack &interactionStack, PanelManager &panelManager) override;
		
		ConstPanel(IScalable *object, Sizing2* sizing, Positioning2* positioning, bool displayed = false);
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
}
