#pragma once

#include "../iPanelInteraction.hpp"

namespace ui {
	class PanelInteraction : public virtual IPanelInteraction {
	protected:
		void copy(PanelInteraction* panelInteraction);
	
	public:
		PanelInteraction();
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		PanelInteraction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
