#pragma once

#include "IE/interaction/IInteraction/IInteraction.hpp"
#include "PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class IPanelInteraction : public virtual IBasicInteraction<Panel&> {
	public:
		struct Make : public virtual IBasicInteraction<Panel&>::Make {
			auto make(PanelActionInitInfo init_info) -> IPanelInteraction* override = 0;
		};
		
		virtual auto set_panel(Panel& panel) -> void = 0;
	};
}