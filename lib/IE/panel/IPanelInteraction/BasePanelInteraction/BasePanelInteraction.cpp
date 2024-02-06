#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	BasePanelInteraction::BasePanelInteraction(PanelActionInitInfo init_info) :
		panel_(&init_info.additional), panel_manager_(&init_info.panel_manager) {
	}
	
	void BasePanelInteraction::set_panel(Panel& panel) {
		this->panel_ = &panel;
	}
}
