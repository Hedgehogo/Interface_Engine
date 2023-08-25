#pragma once

#include "IE/Interaction/IEvent/BasicKeyEvent/BasicBaseKeyEvent/BasicBaseKeyEvent.hpp"
#include "../../PanelInteractionInitInfo/PanelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class PanelEvent : public BaseKeyEvent {
	public:
		PanelEvent();
		
		virtual void init(PanelInteractionInitInfo panelInteractionInitInfo);
		
		void setPanel(Panel& panel);
		
		Panel* getPanel();
		
		PanelEvent* copy() override = 0;
	
	protected:
		Panel* panel;
		IPanelManager* panelManager;
	};
}
