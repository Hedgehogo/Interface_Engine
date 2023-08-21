#pragma once

#include "../IPanelInteraction.hpp"

namespace ui {
	class BasePanelInteraction : public virtual IPanelInteraction {
	protected:
		void copy(BasePanelInteraction* panelInteraction);
	
	public:
		BasePanelInteraction();
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		BasePanelInteraction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
