#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	BasePanelInteraction::BasePanelInteraction(PanelActionInitInfo init_info) :
		panel_(&init_info.additional), panel_manager_(&init_info.panel_manager) {
	}
	
	auto BasePanelInteraction::set_panel(Panel& panel) -> void {
		this->panel_ = &panel;
	}
}
