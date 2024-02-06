#include "DisplayPanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	DisplayPanelAction* DisplayPanelAction::Make::make(PanelActionInitInfo init_info) {
		return new DisplayPanelAction{std::move(*this), init_info};
	}
	
	DisplayPanelAction::DisplayPanelAction(Make&&, PanelActionInitInfo init_info) : PanelAction(init_info) {
	}
	
	void DisplayPanelAction::start_pressed() {
	}
	
	void DisplayPanelAction::while_pressed() {
	}
	
	void DisplayPanelAction::stop_pressed() {
		panel_manager_->display_panel(panel_);
	}
	
	void DisplayPanelAction::while_not_pressed() {
	}
}

orl::Option<ie::DisplayPanelAction::Make> ieml::Decode<char, ie::DisplayPanelAction::Make>::decode(ieml::Node const&) {
	return {{}};
}
