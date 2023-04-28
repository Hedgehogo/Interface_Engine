#pragma once

#include "event/panelEvent.hpp"
#include "../hide/hidePanelInteraction.hpp"
#include "../display/displayPanelInteraction.hpp"
#include "../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public virtual BasePanelInteraction, public OneKeyInteraction {
	public:
		ClickPanelInteraction(PanelEvent* event, Key key);
		
		void init(Panel& panel, IPanelManager& panelManager) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
