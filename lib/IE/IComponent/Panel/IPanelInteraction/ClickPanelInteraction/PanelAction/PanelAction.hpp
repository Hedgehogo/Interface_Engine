#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../PanelActionInitInfo/PanelActionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class PanelAction : public BasicBaseKeyAction<Panel&> {
	public:
		struct Make : public virtual BasicKeyAction<Panel&>::Make {
			PanelAction* make(PanelActionInitInfo initInfo) override = 0;
		};
		
		PanelAction(PanelActionInitInfo initInfo);
		
		PanelAction();
		
		void init(PanelActionInitInfo initInfo) override;
		
		void setPanel(Panel& panel);
		
		Panel* getPanel();
		
		PanelAction* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
