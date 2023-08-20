#pragma once

#include "../../../../Interaction/IInteraction/IInteraction.hpp"
#include "initInfo/panelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class IPanelInteraction : public virtual IInteraction {
	public:
		IPanelInteraction() = default;
		
		virtual void init(PanelInteractionInitInfo panelInteractionInitInfo) = 0;
		
		virtual void setPanel(Panel& panel) = 0;
		
		IPanelInteraction* copy() override = 0;
	};
}
