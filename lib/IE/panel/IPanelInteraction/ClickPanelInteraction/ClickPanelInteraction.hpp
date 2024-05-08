#pragma once

#include "IE/interaction/IInteraction/BasicTouchInteraction/BasicTouchInteraction.hpp"
#include "PanelAction/PanelAction.hpp"
#include "../IHidePanelInteraction/IHidePanelInteraction.hpp"
#include "../IDisplayPanelInteraction/IDisplayPanelInteraction.hpp"

namespace ie {
	class ClickPanelInteraction : public BasicTouchInteraction<Panel&>, public virtual IPanelInteraction {
	public:
		ClickPanelInteraction(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
	};
}