#pragma once
#include "../basePanelInteraction.hpp"

namespace ui {
	class PanelInteraction : public virtual BasePanelInteraction {
	protected:
		Panel* panel;
		IPanelManager* panelManager;
		
		void copy(PanelInteraction* panelInteraction);
	
	public:
		PanelInteraction();
		
		void init(Panel& panel, IPanelManager &panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		PanelInteraction* copy() override = 0;
	};
}
