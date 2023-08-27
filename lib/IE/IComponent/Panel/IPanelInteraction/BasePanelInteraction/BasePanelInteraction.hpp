#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class BasePanelInteraction : public virtual IPanelInteraction {
	public:
		BasePanelInteraction();
		
		void init(PanelInteractionInitInfo initInfo) override;
		
		void setPanel(Panel& panel) override;
		
		BasePanelInteraction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
