#pragma once

#include "event/panelEvent.hpp"
#include "../hide/iHidePanelInteraction.hpp"
#include "../display/iDisplayPanelInteraction.hpp"
#include "../../../../../interaction/iInteraction/oneKey/oneKeyInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public OneKeyInteraction, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key);
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
