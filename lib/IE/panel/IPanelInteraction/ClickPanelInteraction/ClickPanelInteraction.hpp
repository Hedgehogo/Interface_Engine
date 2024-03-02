#pragma once

#include "PanelAction/PanelAction.hpp"
#include "../IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../IDisplayPanelInteraction/IDisplayPanelInteraction.hpp"
#include "IE/interaction/IInteraction/BasicOneKeyInteraction/BasicOneKeyInteraction.hpp"

namespace ie {
	class ClickPanelInteraction : public BasicOneKeyInteraction<Panel&>, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
	};
}