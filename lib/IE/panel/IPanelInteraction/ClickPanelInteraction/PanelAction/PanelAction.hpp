#pragma once

#include "IE/interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class PanelAction : public BasicBaseKeyAction<Panel&> {
	public:
		struct Make : public virtual BasicKeyAction<Panel&>::Make {
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