#pragma once
#include "../basePanel.h"

namespace ui {
	class ConstPanel : public BasePanel {
	public:
		void init(sf::RenderTarget &renderTarget, InteractionStack &interactionStack, InteractionManager &interactionManager, PanelManager &panelManager) override;
		
		ConstPanel(IScalable *object, Sizing2* sizing, Positioning2* positioning, bool displayed = false);
		
		bool isIndependent() override;
		
		bool isFree() override;
		
		ConstPanel* copy() override;
	};
}
