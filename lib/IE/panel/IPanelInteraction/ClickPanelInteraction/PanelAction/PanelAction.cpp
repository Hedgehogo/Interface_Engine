#include "PanelAction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelAction::PanelAction(PanelActionInitInfo init_info) :
		panel_(&init_info.additional), panel_manager_(&init_info.panel_manager) {
	}
	
	void PanelAction::set_panel(Panel& panel) {
		this->panel_ = &panel;
	}
	
	Panel* PanelAction::get_panel() {
		return panel_;
	}
}
