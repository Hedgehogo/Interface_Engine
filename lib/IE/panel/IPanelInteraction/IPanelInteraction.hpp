#pragma once

#include "IE/interaction/IInteraction/IInteraction.hpp"
#include "PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class IPanelInteraction : public virtual IBasicInteraction<Panel&> {
	public:
		struct Make : public virtual IBasicInteraction<Panel&>::Make {
			IPanelInteraction* make(PanelActionInitInfo init_info) override = 0;
		};
		
		virtual void set_panel(Panel& panel) = 0;
	};
}