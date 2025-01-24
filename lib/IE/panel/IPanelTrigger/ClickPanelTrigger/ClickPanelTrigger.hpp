#pragma once

#include "IE/trigger/ITrigger/BasicTouchTrigger/BasicTouchTrigger.hpp"
#include "PanelAction/PanelAction.hpp"
#include "../IHidePanelTrigger/IHidePanelTrigger.hpp"
#include "../IDisplayPanelTrigger/IDisplayPanelTrigger.hpp"

namespace ie {
	class ClickPanelTrigger : public BasicTouchTrigger<Panel&>, public virtual IPanelTrigger {
	public:
		ClickPanelTrigger(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info);
		
		auto set_panel(Panel& panel) -> void override;
	};
}