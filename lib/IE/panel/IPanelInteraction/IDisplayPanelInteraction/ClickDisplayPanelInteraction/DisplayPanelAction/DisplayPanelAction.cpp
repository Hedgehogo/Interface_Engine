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
	
	DisplayPanelAction* DisplayPanelAction::copy() {
		return new DisplayPanelAction{*this};
	}
	
	bool DecodePointer<DisplayPanelAction>::decode_pointer(const YAML::Node&, DisplayPanelAction*& display_panel_action) {
		display_panel_action = new DisplayPanelAction{};
		return false;
	}
}