#include "PanelAction.hpp"
#include "../../../IPanelManager/IPanelManager.hpp"

namespace ie {
	PanelAction::PanelAction(PanelActionInitInfo init_info) :
		panel(&init_info.additional), panel_manager(&init_info.panel_manager) {
	}
	
	PanelAction::PanelAction() : panel(nullptr), panel_manager(nullptr) {
	}
	
	void PanelAction::init(PanelActionInitInfo init_info) {
		this->panel = &init_info.additional;
		this->panel_manager = &init_info.panel_manager;
	}
	
	void PanelAction::set_panel(Panel& panel) {
		this->panel = &panel;
	}
	
	Panel* PanelAction::get_panel() {
		return panel;
	}
}
