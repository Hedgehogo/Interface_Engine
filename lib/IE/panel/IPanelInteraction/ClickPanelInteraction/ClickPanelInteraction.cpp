#include "ClickPanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	ClickPanelInteraction::ClickPanelInteraction(BoxPtr<PanelAction::Make>&& action, Key key, PanelActionInitInfo init_info) :
		BasicOneKeyInteraction<Panel&>({std::move(action), key}, init_info) {
	}
	
	void ClickPanelInteraction::set_panel(Panel& panel) {
		dynamic_cast<PanelAction&>(*action_).set_panel(panel);
	}
}