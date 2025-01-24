#pragma once

#include "IE/trigger/ITrigger/ITrigger.hpp"
#include "PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class IPanelTrigger : public virtual IBasicTrigger<Panel&> {
	public:
		struct Make : public virtual IBasicTrigger<Panel&>::Make {
			auto make(PanelActionInitInfo init_info) -> IPanelTrigger* override = 0;
		};
		
		virtual auto set_panel(Panel& panel) -> void = 0;
	};
}