#include "DisplayPanelAction.hpp"
#include "../../../../BasePanel/Panel/Panel.hpp"

namespace ie {
	void DisplayPanelAction::startPressed() {
	}
	
	void DisplayPanelAction::whilePressed() {
	}
	
	void DisplayPanelAction::stopPressed() {
		panelManager->displayPanel(panel);
	}
	
	void DisplayPanelAction::whileNotPressed() {
	}
	
	DisplayPanelAction* DisplayPanelAction::copy() {
		return new DisplayPanelAction{*this};
	}
	
	bool DecodePointer<DisplayPanelAction>::decodePointer(const YAML::Node&, DisplayPanelAction*& displayPanelAction) {
		displayPanelAction = new DisplayPanelAction{};
		return false;
	}
}