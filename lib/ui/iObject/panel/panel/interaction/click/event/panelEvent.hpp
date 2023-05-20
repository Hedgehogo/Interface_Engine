#pragma once

#include "../../../../../../interaction/event/key/simple/keyEventSimple.hpp"
#include "../../initInfo/panelInteractionInitInfo.hpp"

namespace ui {
	class Panel;
	
	class IPanelManager;
	
	class PanelEvent : public KeyEvent_Simple {
	protected:
		Panel* panel;
		IPanelManager* panelManager;
		
		void copy(PanelEvent* panelEvent);
	
	public:
		PanelEvent();
		
		virtual void init(PanelInteractionInitInfo panelInteractionInitInfo);
		
		void setPanel(Panel& panel);
		
		Panel* getPanel();
		
		PanelEvent* copy() override = 0;
	};
}
