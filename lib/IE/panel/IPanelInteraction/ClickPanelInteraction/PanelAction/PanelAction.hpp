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
		
		void set_panel(Panel& panel);
		
		Panel* get_panel();
		
	protected:
		Panel* panel_;
		IPanelManager* panel_manager_;
	};
}