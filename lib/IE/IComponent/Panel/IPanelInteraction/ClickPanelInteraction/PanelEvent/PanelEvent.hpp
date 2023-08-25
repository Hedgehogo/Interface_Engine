#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "../../PanelInteractionInitInfo/PanelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class PanelEvent : public BasicBaseKeyEvent<Panel&> {
	public:
		PanelEvent();
		
		void init(PanelInteractionInitInfo initInfo) override;
		
		void setPanel(Panel& panel);
		
		Panel* getPanel();
		
		PanelEvent* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
