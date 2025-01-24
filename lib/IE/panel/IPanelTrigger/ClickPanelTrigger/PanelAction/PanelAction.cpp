#include "PanelAction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelAction::PanelAction(PanelActionInitInfo init_info) :
		panel_(&init_info.additional), panel_manager_(&init_info.panel_manager) {
	}
	
	auto PanelAction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
	
	auto PanelAction::get_panel() -> Panel* {
		return panel_;
	}
}
