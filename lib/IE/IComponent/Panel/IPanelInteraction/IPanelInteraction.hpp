#pragma once

#include "../../../Interaction/IInteraction/IInteraction.hpp"
#include "PanelInteractionInitInfo/PanelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class IPanelInteraction : public virtual IBaseInteraction {
	public:
		IPanelInteraction() = default;
		
		virtual void init(PanelInteractionInitInfo panelInteractionInitInfo) = 0;
		
		virtual void setPanel(Panel& panel) = 0;
		
		IPanelInteraction* copy() override = 0;
	};
}