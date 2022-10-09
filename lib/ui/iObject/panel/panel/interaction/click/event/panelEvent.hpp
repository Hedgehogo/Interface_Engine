#pragma once
#include "../../../../../../interaction/event/button/simple/buttonEventSimple.hpp"

namespace ui {
	class Panel;
	class IPanelManager;
	class PanelEvent : public ButtonEvent_Simple {
	protected:
		Panel* panel;
		IPanelManager* panelManager;
		
		void copy(PanelEvent* panelEvent);
		
	public:
		PanelEvent();
		
		virtual void init(Panel& panel, IPanelManager &panelManager);
		
		void setPanel(Panel& panel);
		
		Panel* getPanel();
		
		PanelEvent* copy() override = 0;
	};
}
