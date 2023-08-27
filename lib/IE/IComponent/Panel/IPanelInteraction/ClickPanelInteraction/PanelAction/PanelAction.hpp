#pragma once

#include "IE/Interaction/IAction/BasicKeyAction/BasicBaseKeyAction/BasicBaseKeyAction.hpp"
#include "../../PanelInteractionInitInfo/PanelInteractionInitInfo.hpp"

namespace ie {
	class Panel;
	
	class IPanelManager;
	
	class PanelAction : public BasicBaseKeyAction<Panel&> {
	public:
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
