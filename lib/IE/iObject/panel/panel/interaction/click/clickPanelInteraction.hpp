#pragma once

#include "event/panelEvent.hpp"
#include "../hide/iHidePanelInteraction.hpp"
#include "../display/iDisplayPanelInteraction.hpp"
#include "../../../../../Interaction/IInteraction/OneKeyInteraction/OneKeyInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public OneKeyInteraction, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key);
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
