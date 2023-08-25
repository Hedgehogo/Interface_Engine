#pragma once

#include "PanelEvent/PanelEvent.hpp"
#include "../IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../IDisplayPanelInteraction/IDisplayPanelInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"

namespace ui {
	class ClickPanelInteraction : public BasicOneKeyInteraction<Panel&>, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelEvent>&& event, Key key);
		
		void init(PanelInteractionInitInfo initInfo) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
