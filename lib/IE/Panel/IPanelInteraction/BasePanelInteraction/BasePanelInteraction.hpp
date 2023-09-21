#pragma once

#include "../IPanelInteraction.hpp"

namespace ie {
	class BasePanelInteraction : public virtual IPanelInteraction {
	public:
		BasePanelInteraction(PanelActionInitInfo initInfo);
		
		BasePanelInteraction();
		
		void init(PanelActionInitInfo initInfo) override;
		
		void setPanel(Panel& panel) override;
		
		BasePanelInteraction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
