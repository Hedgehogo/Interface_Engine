#pragma once
#include "../basePanelInteraction.h"

namespace ui {
	class PanelInteraction : public virtual BasePanelInteraction {
	protected:
		Panel* panel;
		PanelManager* panelManager;
		
		void copy(PanelInteraction* panelInteraction);
	
	public:
		PanelInteraction();
		
		void init(Panel& panel, PanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		PanelInteraction* copy() override = 0;
	};
}
