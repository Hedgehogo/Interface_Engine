#pragma once

#include "../../../../interaction/iInteraction/iInteraction.hpp"
#include "initInfo/panelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class BasePanelInteraction : public virtual IInteraction {
	public:
		BasePanelInteraction() = default;
		
		virtual void init(PanelInteractionInitInfo panelInteractionInitInfo) = 0;
		
		virtual void setPanel(Panel& panel) = 0;
		
		BasePanelInteraction* copy() override = 0;
	};
}
