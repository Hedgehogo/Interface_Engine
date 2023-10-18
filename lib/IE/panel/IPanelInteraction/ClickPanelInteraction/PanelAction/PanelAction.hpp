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
		
		PanelAction();
		
		void init(PanelActionInitInfo init_info) override;
		
		void set_panel(Panel& panel);
		
		Panel* get_panel();
		
		PanelAction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panel_manager;
	};
}