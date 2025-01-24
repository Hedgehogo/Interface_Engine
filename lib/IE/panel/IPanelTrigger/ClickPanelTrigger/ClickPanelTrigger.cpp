#include "ClickPanelTrigger.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	ClickPanelTrigger::ClickPanelTrigger(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info) :
		BasicTouchTrigger<Panel&>({std::move(action), key}, init_info) {
	}
	
	auto ClickPanelTrigger::set_panel(Panel& panel) -> void {
		dynamic_cast<PanelAction&>(*action_).set_panel(panel);
	}
}