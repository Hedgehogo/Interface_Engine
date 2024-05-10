#pragma once

#include "IE/interaction/IAction/BasicTouchAction/BasicTouchAction.hpp"
#include "../../PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class PanelAction : public BasicTouchAction<Panel&> {
	public:
		struct Make : public virtual BasicTouchAction<Panel&>::Make {
			PanelAction* make(PanelActionInitInfo init_info) override = 0;
		};
		
		PanelAction(PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void;
		
		auto get_panel() -> Panel*;
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}