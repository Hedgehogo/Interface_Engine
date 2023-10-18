#include "BasePanelInteraction.hpp"
#include "../../IPanelManager/IPanelManager.hpp"

namespace ie {
	BasePanelInteraction::BasePanelInteraction(PanelActionInitInfo init_info) :
		panel(&init_info.additional), panel_manager(&init_info.panel_manager) {
	}
	
	BasePanelInteraction::BasePanelInteraction() : panel(nullptr), panel_manager(nullptr) {
	}
	
	void BasePanelInteraction::init(PanelActionInitInfo init_info) {
		this->panel = &init_info.additional;
		this->panel_manager = &init_info.panel_manager;
	}
	
	void BasePanelInteraction::set_panel(Panel& panel) {
		this->panel = &panel;
	}
}
