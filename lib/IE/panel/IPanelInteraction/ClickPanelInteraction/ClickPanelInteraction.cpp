#include "ClickPanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info) :
		BasicTouchInteraction<Panel&>({std::move(action), key}, init_info) {
	}
	
	auto ClickPanelInteraction::set_panel(Panel& panel) -> void {
		dynamic_cast<PanelAction&>(*action_).set_panel(panel);
	}
}