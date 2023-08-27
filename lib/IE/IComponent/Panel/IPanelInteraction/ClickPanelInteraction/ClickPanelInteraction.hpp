#pragma once

#include "IE/IComponent/Panel/IPanelInteraction/ClickPanelInteraction/PanelAction/PanelAction.hpp"
#include "../IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../IDisplayPanelInteraction/IDisplayPanelInteraction.hpp"
#include "IE/Interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"

namespace ie {
	class ClickPanelInteraction : public BasicOneKeyInteraction<Panel&>, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelAction>&& action, Key key);
		
		void init(PanelInteractionInitInfo initInfo) override;
		
		void setPanel(Panel& panel) override;
		
		ClickPanelInteraction* copy() override = 0;
	};
}
