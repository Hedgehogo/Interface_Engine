#pragma once

#include "PanelEvent/PanelEvent.hpp"
#include "../IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../IDisplayPanelInteraction/IDisplayPanelInteraction.hpp"
#include "../../../../Interaction/IInteraction/OneKeyInteraction/OneKeyInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public OneKeyInteraction, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key);
		
		void init(PanelInteractionInitInfo panelInteractionInitInfo) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
