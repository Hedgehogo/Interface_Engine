#pragma once

#include "IE/interaction/IInteraction/IInteraction.hpp"
#include "PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class IPanelInteraction : public virtual IBasicInteraction<Panel&> {
	public:
		struct Make : public virtual IBasicInteraction<Panel&>::Make {
			IPanelInteraction* make(PanelActionInitInfo initInfo) override = 0;
		};
		
		virtual void setPanel(Panel& panel) = 0;
		
		IPanelInteraction* copy() override = 0;
	};
}