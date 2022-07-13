#pragma once
#include "../../../../../../interaction/event/button/simple/buttonEventSimple.h"

namespace ui {
	class Panel;
	class PanelManager;
	class PanelEvent : public ButtonEvent_Simple {
	protected:
		Panel* panel;
		PanelManager* panelManager;
		
		void copy(PanelEvent* panelEvent);
		
	public:
		PanelEvent();
		
		virtual void init(Panel& panel, PanelManager& panelManager);
		
		void setPanel(Panel& panel);
		
		PanelEvent* copy() override = 0;
	};
}
